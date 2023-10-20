#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

//Error-introduction menu
void options(){
    printf("Program operation: ./executable -option parameter\n");
    printf("Options: \n");
    printf("        -h, --help->Print available options\n");
    printf("        -u, --user->User login/UID\n");
    printf("        -a, --active->Current user\n");
    printf("        -m, --maingroup->Main group information\n");
    printf("        -g, --group->Group name/GID\n");
    printf("        -s, --allgroups->Show info of all system groups\n");
    printf("Possible combinations:\n");
    printf("    --help, along with any (others are ignored)\n");
    printf("    empty\n");
    printf("    --user <user>\n");
    printf("    --active\n");
    printf("    --active --maingroup\n");
    printf("    --group <group>\n");
    printf("    --allgroups\n");
    exit(-1);
}

int main(int argc, char *argv[]) {
    //Variables from /etc/password-group
    char *lgn;
    struct passwd *pw;
    struct group *gr;
    
    //Getopt_long
    bool aflag=false;
    bool hflag=false;
    bool sflag=false;
    bool mflag=false;
    char *uvalue=NULL;
    char *gvalue=NULL;
    int c;
    if(argc<2){
        printf("Opción por defecto\n");
        if((lgn=getenv("USER"))==NULL || (pw=getpwnam(lgn))==NULL){
            printf("Error while entering the username\n");
            options();     
        }
        printf("Name: %s\n", pw->pw_gecos);
        printf("Login: %s\n", pw->pw_name);
        printf("Password: %s\n", pw->pw_passwd);
        printf("UID: %d\n", pw->pw_uid);
        printf("Home: %s\n", pw->pw_dir);
        printf("Shell: %s\n", pw->pw_shell);
        printf("Main group number: %d\n", pw->pw_gid);
        gr=getgrgid(pw->pw_gid);
        printf("Main group name: %s\n", gr->gr_name);
    }
    
    //Structure to be used by getopt_long
    static struct option long_options[] = {
        {"user", required_argument, NULL, 'u' },
        {"group", required_argument, NULL, 'g' },
        {"active", no_argument, NULL, 'a' },
        {"maingroup", no_argument, NULL, 'm' },
        {"allgroups", no_argument, NULL, 's' },
        {0, 0, 0, 0}
    };

    while((c=getopt_long(argc, argv, "h,s,a,m,g:u:", long_options, NULL))!=-1) {
        switch (c){
            //Print available options
            case 'h':
                hflag=true;
            break;
            //Show information of all system groups
            case 's':
                sflag=true;
            break;
            //Current user
            case 'a':            
                aflag=true;       
            break;
            //Main group information
            case 'm':
               mflag=true;     
            break;
            //Group name
            case 'g': 
              gvalue=optarg;    
            break;
            //User login
            case 'u':
                uvalue=optarg;
            break; 
            //In case of any character       
            case '?':
               options();
            break;
            default:
                abort();
        }
    }
    //Error control for options
    if((sflag==true) && (mflag==true)){
        printf("Simultaneous options not available: -s -m\n");
        options();
    }
    if((uvalue!=NULL) && (aflag==true)){
        printf("Simultaneous options not available: -u -a\n");
        options();
    }
    if((uvalue!=NULL) && (sflag==true)){
        printf("Simultaneous options not available: -u -s\n");
        options();
    }  
    if((uvalue!=NULL) && (gvalue!=NULL)){
        printf("Simultaneous options not available: -u -g\n");
        options();
    } 
    if((gvalue!=NULL) && (mflag==true)){
        printf("Simultaneous options not available: -g -m\n");
        options();
    } 
    if((sflag==true) && (mflag==true)){
        printf("Simultaneous options not available: -s -m\n");
        options();
    } 
    if((sflag==true) && (aflag==true)){
        printf("Simultaneous options not available: -s -a\n");
        options();
    } 
    if((mflag==true) && (aflag==false) && (uvalue==NULL)){
        printf("Option not available: -m\n");
        options();
    }

    //Options
    if(hflag==true){
        options(); 
    }

    //Reading groups from the /etc/group file
    if(sflag==true){  
            char * line=NULL;
            size_t len=0; 
            ssize_t read;
            char* token;           
            char delimiter[] = ":";           
            FILE * fp;           
            fp=fopen("/etc/group", "r");
            if(fp==NULL){
                exit(EXIT_FAILURE);
            } 
            while((read=getline(&line, &len, fp))!=-1){                
                token=strtok(line, delimiter);
                gr=getgrnam(token);
                printf("Group name: %s.\n", gr->gr_name);
                printf("Identifier: %d\n", gr->gr_gid);
                printf("-----------------------------------\n");
            }
            if(line){
                free(fp);
            }
    }
    //Selected options
    if(aflag==true){
        if((lgn=getenv("USER"))==NULL || (pw=getpwnam(lgn))==NULL){
            printf("Error entering the username\n");
            options();     
        }
        printf("Name: %s\n", pw->pw_gecos);
        printf("Login: %s\n", pw->pw_name);
        printf("Password: %s\n", pw->pw_passwd);
        printf("UID: %d\n", pw->pw_uid);
        printf("Home: %s\n", pw->pw_dir);
        printf("Shell: %s\n", pw->pw_shell);
        printf("Main group number: %d\n", pw->pw_gid);
        if(mflag==true){
            gr=getgrgid(pw->pw_gid);
            printf("Main group name: %s\n", gr->gr_name);
        }            
    }   
    if(uvalue!=NULL){
        char *endptr;
        strtol(uvalue, &endptr, 10);
        if(((*uvalue)!='\0') && ((*endptr)=='\0')){
            if((pw=getpwuid(atoi(uvalue)))==NULL){
                printf("Error entering the user name-identifier\n");
                options(); 
            }
            else{
                printf("Name: %s\n", pw->pw_gecos); 
                printf("Login: %s\n", pw->pw_name);
                printf("Password: %s\n", pw->pw_passwd);
                printf("UID: %d\n", pw->pw_uid);
                printf("Home: %s\n", pw->pw_dir);
                printf("Shell: %s\n", pw->pw_shell);
                printf("Main group number: %d\n", pw->pw_gid);
                if(mflag==true){
                    gr=getgrgid(pw->pw_gid);
                    printf("Main group name: %s\n", gr->gr_name);
                }
            }
        }
        else{
            if((lgn=uvalue)==NULL || (pw=getpwnam(lgn))==NULL){
                printf("Error entering the user name-identifier\n");
                options(); 
            }
            else{
                printf("Name: %s\n", pw->pw_gecos); 
                printf("Login: %s\n", pw->pw_name);
                printf("Password: %s\n", pw->pw_passwd);
                printf("UID: %d\n", pw->pw_uid);
                printf("Home: %s\n", pw->pw_dir);
                printf("Shell: %s\n", pw->pw_shell);
                printf("Main group number: %d\n", pw->pw_gid);
                if(mflag==true){
                    gr=getgrgid(pw->pw_gid);
                    printf("Main group name: %s\n", gr->gr_name);
                }
            }
        }     
    }
    if(gvalue!=NULL){
        char *endptr;
        strtol(gvalue, &endptr, 10);
        if(((*gvalue)!='\0') && ((*endptr)=='\0')){
            if((gr=getgrgid(atoi(gvalue)))==NULL){
                printf("Error entering the user name-identifier\n");
                options();
            }
            else{
                printf("Group number: %d\n", gr->gr_gid);
                printf("Main group name: %s\n", gr->gr_name);
            }
        } 
        else{
            if((lgn=gvalue)==NULL || (pw=getpwnam(lgn))==NULL){
                printf("Error entering the user name-identifier\n");
                options();
            }
            else{
                printf("Main group number: %d\n", pw->pw_gid);
                gr=getgrgid(pw->pw_gid);
                printf("Main group name: %s\n", gr->gr_name);
            }     
        } 
    }
    return 0;       
}