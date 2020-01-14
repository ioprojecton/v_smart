char c=0;
    for(char i=0,flag=0;i<strlen(a);i++){
        if(a[i]==' ' && a[i+1]==' ') continue;
        else if(a[i]==' ' && a[i+1]!=' ' && !flag) {
                flag=1;
                continue;}
            else b[c++]=a[i];
    }
    b[c]='\0';
