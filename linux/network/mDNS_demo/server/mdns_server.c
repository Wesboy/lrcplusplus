#include <avahi-client/client.h>
#include <avahi-client/publish.h>
#include <avahi-common/simple-watch.h>
#include <avahi-common/error.h>
#include <avahi-common/alternative.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static AvahiEntryGroup *group = NULL;
static AvahiSimplePoll *simple_poll = NULL;
static void create_services(AvahiSimplePoll *poll, const char *name);

void sigint_handler(int sig) {
    printf("\nSIGINT received, shutting down...\n");
    avahi_simple_poll_quit(simple_poll);
}

static void entry_group_callback(
    AvahiEntryGroup *g,
    AvahiEntryGroupState state,
    void *userdata) {
    
    group = g;

    switch (state) {
        case AVAHI_ENTRY_GROUP_ESTABLISHED:
            printf("Service '%s' successfully established.\n", (char*)userdata);
            break;
            
        case AVAHI_ENTRY_GROUP_COLLISION: {
            char *new_name = avahi_alternative_service_name((char*)userdata);
            printf("Service name collision, renaming service to '%s'\n", new_name);
            avahi_entry_group_free(g);
            group = NULL;
            create_services(simple_poll, new_name);
            free(new_name);
            break;
        }
            
        case AVAHI_ENTRY_GROUP_FAILURE:
            fprintf(stderr, "Failed to establish service: %s\n", 
                    avahi_strerror(avahi_client_errno(avahi_entry_group_get_client(g))));
            avahi_simple_poll_quit(simple_poll);
            break;
            
        default:
            break;
    }
}

static void create_services(AvahiSimplePoll *poll, const char *name) {
    AvahiClient *client = avahi_client_new(
        avahi_simple_poll_get(poll), 
        0, 
        NULL, 
        NULL, 
        NULL
    );
    
    if (!client) {
        fprintf(stderr, "Failed to create client: %s\n", avahi_strerror(avahi_client_errno(client)));
        goto fail;
    }
    
    group = avahi_entry_group_new(client, entry_group_callback, (void*)name);
    
    if (!group) {
        fprintf(stderr, "Failed to create entry group: %s\n", avahi_strerror(avahi_client_errno(client)));
        goto fail;
    }
    
    int ret;
    ret = avahi_entry_group_add_service(
        group,
        AVAHI_IF_UNSPEC,
        AVAHI_PROTO_UNSPEC,
        0,  // flags
        name,
        "_demo-service._tcp",  // service type
        NULL,  // domain
        NULL,  // host
        12345, // port
        NULL   // TXT record
    );
    
    if (ret < 0) {
        fprintf(stderr, "Failed to add service: %s\n", avahi_strerror(ret));
        goto fail;
    }
    
    ret = avahi_entry_group_commit(group);
    if (ret < 0) {
        fprintf(stderr, "Failed to commit entry group: %s\n", avahi_strerror(ret));
        goto fail;
    }
    
    return;
    
fail:
    if (group) avahi_entry_group_free(group);
    if (client) avahi_client_free(client);
    avahi_simple_poll_quit(simple_poll);
}

int main(int argc, char** argv) {
    const char *service_name = "My Demo Service";
    
    if (argc > 1) {
        service_name = argv[1];
    }
    
    signal(SIGINT, sigint_handler);
    
    simple_poll = avahi_simple_poll_new();
    if (!simple_poll) {
        fprintf(stderr, "Failed to create simple poll object\n");
        return 1;
    }
    
    create_services(simple_poll, service_name);
    
    printf("mDNS server running. Publishing service: '%s'\n", service_name);
    printf("Press Ctrl+C to exit...\n");
    
    avahi_simple_poll_loop(simple_poll);
    
    if (group) avahi_entry_group_free(group);
    if (simple_poll) avahi_simple_poll_free(simple_poll);
    
    return 0;
}
