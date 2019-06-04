#include <iostream>

using namespace std;

int main(void)
{
	bool blval;
	char chval;
	int ival;
	float flval;
	double dbval;
	//void vval;
	wchar_t wval;
	
	
	cout<<"bool val addr:"<<&blval<<endl;
	cout<<"char val addr:"<<&chval<<endl;
	cout<<"int  val addr:"<<&ival<<endl;
	cout<<"float val addr:"<<&flval<<endl;
	cout<<"double val addr:"<<&dbval<<endl;
	//cout<<"void val addr:"<<&vval<<endl;
	cout<<"wchar_t val addr:"<<&wval<<endl;
	
	
	printf("bool val size:%p",(void *)&blval-(void *)&chval);
	printf("char val size:%p",(void *)&chval-(void *)&ival);
	printf("int  val size:%p",(void *)&ival-(void *)&flval);
	printf("float val size:%p",(void *)&flval-(void *)&dbval);
	printf("double val size:%p",(void *)&dbval-(void *)&wval);
	cout<<"char val size:"<<(void *)&chval-(void *)&ival<<endl;
	cout<<"int  val size:"<<(void *)&ival-(void *)&flval<<endl;
	cout<<"float val size:"<<(void *)&flval-(void *)&dbval<<endl;
	cout<<"double val size:"<<(void *)&dbval-(void *)&wval<<endl;
	//cout<<"void val size:"<<&vval<<endl;
	cout<<"wchar_t val size:"<<&wval<<endl;
	return 0;
}