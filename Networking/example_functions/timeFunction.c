#include<stdio.h>
#include<time.h>
#include <locale.h>


int main(){
	time_t currentTime;
	struct tm* timeInfo;
	char outputString [80];
	currentTime=time(NULL);
	setlocale(LC_ALL,"");
	timeInfo=localtime(&currentTime);
	/* FORMATS TO USE WITH THE timeInfo STRUCTURE
    %B - Full month name (January, ...)
    %b - Abbreviated month name (Jan, ...)
    %A - Full day of the week (Sunday, ...)
    %a - Abbreviated day of the week (Sun, ...)
    %d - Day of the month in two digits (01-31)
    %m - Month in two digits (01-12)
    %D - Date in the format %m/%d/%y
    %H - Hour in two digits (00-23)
    %M - Minutes in two digits
    %S - Seconds in two digits
    %Y - Four-digit year
    */
	strftime(outputString,80,"%A, %d of %B\n", timeInfo);
	printf("outputString: %s", outputString);
	return 0;
}
