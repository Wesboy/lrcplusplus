#include <avahi-client/client.h>
#include <avahi-client/lookup.h>
#include <avahi-common/simple-watch.h>
#include <avahi-common/error.h>
#include <avahi-common/malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static AvahiSimplePoll *simple_poll = NULL;
static int service_count = 0;

void sigint_handler(int sig) {
    printf("\nSIGINT received, shutting down...\n");
    avahi_simple_poll_quit(simple_poll);
}

static void resolve_callback(
    AvahiServiceResolver *r,
    AvahiIfIndex interface,
    AvahiProtocol protocol,
    AvahiResolverEvent event,
    const char *name,
    const char *type,
    const char *domain,
    const char *host_name,
    const AvahiAddress *address,
    uint16_t port,
    AvahiStringList *txt,
    AvahiLookupResultFlags flags,
    void* userdata) {
    
    switch (event) {
        case AVAHI_RESOLVER_FOUND: {
            char addr[AVAHI_ADDRESS_STR_MAX];
            avahi_address_snprint(addr, sizeof(addr), address);
            
            printf("\n=== Service Resolved ===\n");
            printf("Name:        %s\n", name);
            printf("Type:        %s\n", type);
            printf("Domain:      %s\n", domain);
            printf("Host:        %s\n", host_name);
            printf("Address:     %s\n", addr);
            printf("Port:        %d\n", port);
            printf("Interface:   %d\n", interface);
            printf("Protocol:    %s\n", 
                   protocol == AVAHI_PROTO_INET ? "IPv4" : "IPv6");
            
            if (txt) {
                printf("TXT records:\n");
                for (AvahiStringList *t = txt; t; t = avahi_string_list_get_next(t)) {
                    char *key, *value;
                    if (avahi_string_list_get_pair(t, &key, &value, NULL) == 0) {
                        printf("  %s = %s\n", key, value ? value : "(null)");
                        avahi_free(key);
                        avahi_free(value);
                    }
                }
            }
            
            service_count++;
            break;
        }
            
        case AVAHI_RESOLVER_FAILURE:
            fprintf(stderr, "Resolver error: %s\n", 
                    avahi_strerror(avahi_client_errno(avahi_service_resolver_get_client(r))));
            break;
    }
    
    avahi_service_resolver_free(r);
}

static void browse_callback(
    AvahiServiceBrowser *b,
    AvahiIfIndex interface,
    AvahiProtocol protocol,
    AvahiBrowserEvent event,
    const char *name,
    const char *type,
    const char *domain,
    AvahiLookupResultFlags flags,
    void *userdata) {
    
    AvahiClient *client = (AvahiClient*)userdata;
    
    switch (event) {
        case AVAHI_BROWSER_NEW: {
            printf("Found service: %s of type %s in domain %s\n", name, type, domain);
            
            if (!(avahi_service_resolver_new(
                client,
                interface,
                protocol,
                name,
                type,
                domain,
                AVAHI_PROTO_UNSPEC,
                0,  // flags
                resolve_callback,
                NULL))) {
                
                fprintf(stderr, "Failed to create resolver: %s\n", 
                        avahi_strerror(avahi_client_errno(client)));
            }
            break;
        }
            
        case AVAHI_BROWSER_REMOVE:
            printf("Service removed: %s\n", name);
            break;
            
        case AVAHI_BROWSER_ALL_FOR_NOW:
            printf("Service discovery complete. Found %d services.\n", service_count);
            break;
            
        case AVAHI_BROWSER_FAILURE:
            fprintf(stderr, "Browser error: %s\n", 
                    avahi_strerror(avahi_client_errno(client)));
            avahi_simple_poll_quit(simple_poll);
            break;
    }
}

int main(int argc, char** argv) {
    signal(SIGINT, sigint_handler);
    
    simple_poll = avahi_simple_poll_new();
    if (!simple_poll) {
        fprintf(stderr, "Failed to create simple poll object\n");
        return 1;
    }
    
    AvahiClient *client = avahi_client_new(
        avahi_simple_poll_get(simple_poll),
        0,  // flags
        NULL, // callback
        NULL, // userdata
        NULL  // ret_error
    );
    
    if (!client) {
        fprintf(stderr, "Failed to create client: %s\n", avahi_strerror(avahi_client_errno(client)));
        return 1;
    }
    
    AvahiServiceBrowser *browser = avahi_service_browser_new(
        client,
        AVAHI_IF_UNSPEC,
        AVAHI_PROTO_UNSPEC,
        "_demo-service._tcp",  // service type
        NULL,  // domain
        0,     // flags
        browse_callback,
        client
    );
    
    if (!browser) {
        fprintf(stderr, "Failed to create browser: %s\n", avahi_strerror(avahi_client_errno(client)));
        return 1;
    }
    
    printf("mDNS client running. Discovering services of type: '_demo-service._tcp'\n");
    printf("Press Ctrl+C to exit...\n");
    
    avahi_simple_poll_loop(simple_poll);
    
    if (browser) avahi_service_browser_free(browser);
    if (client) avahi_client_free(client);
    if (simple_poll) avahi_simple_poll_free(simple_poll);
    
    return 0;
}