#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 100
struct flight_record {
    char flight_name[100];
        int flight_id;
        int flight_cap;
        int flight_arr;
        int flight_dep;
        int flight_stay;
        int flight_delay;
        char flight_class[100];
        char flight_status[100];
        struct flight_record *next;
};

struct flightupdate {
    char fname[100];
    int fid;
    char status[100];
    char promote_status[100];
    int fdeltime;
    struct flightupdate *next;
};


void print(struct flight_record*);
struct flight_record *InsertAtStart(struct flight_record*,char [],int,int,int,int,char [],char [],int);
int insert(char [],int,int,int,int,char [],char [],int);
void delete_rec(struct flight_record*,int);
int getNumFlights(struct flight_record*);
int isEmpty(struct flight_record*);
int isFull(struct flight_record*);
int setStaytime(int,int);
void geFlightWithtLongeststay(struct flight_record*);
void getSortedOnArrivalTime(struct flight_record*);
void getSortedOnDepartureTime(struct flight_record *);
void getSortedOnStayTime(struct flight_record *);
struct flight_record *getClassList(struct flight_record*,char []);
void UpdateFlightStatus(struct flight_record*,struct flight_record*);
struct flight_record *list_unique(struct flight_record*);

struct flight_record *nptr;
struct flight_record *flight;

struct flightupdate *uptr;
struct flightupdate *vptr;

void print(struct flight_record *pptr)
{
    while( pptr != NULL )
    {
            printf("   Name : %s\n",pptr->flight_name);
            printf("   ID : %d\n",pptr->flight_id);
            printf("   Arrival Time : %d\n",pptr->flight_arr);
            printf("   Departure Time : %d\n",pptr->flight_dep);
            printf("   Stay Time : %d hr %d min\n",(pptr->flight_stay)/100,(pptr->flight_stay)%100);
            printf("   Capacity : %d\n",pptr->flight_cap);
            printf("   Class : %s\n",pptr->flight_class);
            printf("   Status : %s\n\n",pptr->flight_status);
            pptr = pptr->next;
    }
}

struct flight_record *InsertAtStart(struct flight_record *lptr,char name[100],int id,int capa,int arrt,int dept,char fclass[7],char Fstatus[],int delaytime)
{
    struct flight_record *nptr,*ptr;
    nptr=(struct flight_record*)malloc(sizeof(struct flight_record));
    strcpy(nptr->flight_name,name);
    nptr->flight_id=id;
    nptr->flight_cap=capa;
    nptr->flight_arr=arrt;
    nptr->flight_dep=dept;
    strcpy(nptr->flight_class,fclass);
    strcpy(nptr->flight_status,Fstatus);
    nptr->flight_delay=delaytime;
    nptr->flight_stay=setStaytime(arrt,dept);
    nptr->next=lptr;
    lptr=nptr;
    return lptr;
}

int insert(char name[100],int ID,int cap,int arr,int dep,char flightclass[100],char flistatus[100],int delaytime)
{
    struct flight_record *lptr,*ptr,*del;
    lptr = flight;
    ptr = flight;
    del=flight;
    int count,flag=0;
    while(ptr != NULL)
    {
        if(ptr->flight_id <= 0)
        {
            delete_rec(del,ptr->flight_id);
        }
        ptr=ptr->next;
    }
    while(lptr!= NULL && flag==0)
    {
        if(lptr->flight_id == ID || strcmp(lptr->flight_name,name) == 0)
        {
            flag=1;
            lptr->flight_id=ID;
            strcpy(lptr->flight_name,name);
            lptr->flight_arr=arr;
            lptr->flight_dep=dep;
            lptr->flight_cap=cap;
            strcpy(lptr->flight_class,flightclass);
            strcpy(lptr->flight_status,flistatus);
            lptr->flight_stay=setStaytime(lptr->flight_arr,lptr->flight_dep);
            lptr->flight_delay=delaytime;
        }
        else
            lptr=lptr->next;
    }
    if(!isFull(nptr) && flag==0)
    {
        flight=InsertAtStart(flight,name,ID,cap,arr,dep,flightclass,flistatus,delaytime);
    }
    flight=sort(flight,4);
    flight=sort(flight,6);
    print(flight);
        if(!isFull(nptr))
            return 1;
        else
            return 0;
}

void delete_rec(struct flight_record *lptr,int deleId)
{
    int count=getNumFlights(flight);
    struct flight_record *nptr;
    nptr=lptr;
    int flag=0;
    if(nptr->flight_id == deleId)
    {
        struct flight_record *del;
        del=nptr;
        nptr=nptr->next;
        free(del);
        lptr=nptr;
        printf("Deleted the flight record successfully!!\n\n");
    }
    else
    {
        while(nptr->next != NULL && flag==0)
        {
            if((nptr->next)->flight_id == deleId)
            {
                flag=1;
                struct flight_record *del;
                del=nptr->next;
                nptr->next=(nptr->next)->next;
                free(del);
                printf("Deleted the flight record successfully!!\n\n");
            }
            else
                nptr=nptr->next;
        }
    }
    flight=lptr;
    int count2=getNumFlights(flight);
    if(count2==count)
        printf("Delete operation not done as record of flight is not found\n");
    flight=sort(flight,4);
    flight=sort(flight,6);
    print(flight);
}
int getNumFlights(struct flight_record *lptr)
{
    int count = 0;
    while(lptr != NULL)
    {
        count++;
        lptr=lptr->next;
    }
    return count;
}
int isEmpty(struct flight_record *fptr)
{
    if(getNumFlights(fptr) == 0)
        return 1;
    else
        return 0;
}
int isFull(struct flight_record *fptr)
{
    if(getNumFlights(fptr) == size)
        return 1;
    else
        return 0;
}
int setStaytime(int arrtime,int depttime)
{
    int hr,min,time;
    if(depttime>=arrtime)
    {
        hr=depttime/100 - arrtime/100;
        if(depttime%100 < arrtime%100)
        {
            hr=hr-1;
            min=60 + depttime%100 - arrtime%100;
        }
        else
            min= depttime%100 - arrtime%100;
    }
    else
    {
        hr= 24 - arrtime/100 + depttime/100 ;
        if(arrtime%100 > 0)
        {
            hr=hr-1;
            min=60-arrtime%100 + depttime%100;
        }
        else min =depttime%100;
        if(min >=60)
        {
            min=min-60;
            hr=hr+1;
        }
    }
    time = hr*100 + min;
    return time;
}
void geFlightWithtLongeststay(struct flight_record *lptr)
{
    struct flight_record* node;
    node = lptr;
    while(lptr != NULL)
    {
        if(node->flight_stay < lptr->flight_stay)
        {
            node=lptr;
        }
        lptr=lptr->next;
    }
    printf("   Name : %s\n",node->flight_name);
        printf("   ID : %d\n",node->flight_id);
        printf("   Arrival Time : %d\n",node->flight_arr);
        printf("   Departure Time : %d\n",node->flight_dep);
        printf("   Stay Time : %d hr %d min\n",(node->flight_stay)/100,(node->flight_stay)%100);
        printf("   Delay Time : %d\n",node->flight_delay);
        printf("   Capacity : %d\n",node->flight_cap);
        printf("   Status : %s\n",node->flight_status);
        printf("   Class : %s\n\n",node->flight_class);
}

//basic merge function
struct flight_record *merge(struct flight_record *lptr1,struct flight_record *lptr2,int t)
{
    struct flight_record *result,*tail,*p,*q;
    p = lptr1;
    q = lptr2;
    if(lptr1 == NULL)
    {
        result = lptr2;
    }
    else if(lptr2 == NULL)
    {
        result = lptr1;
    }
    else
    {
        if(t==1 ? (lptr1->flight_arr) < (lptr2->flight_arr) : t==2 ? (lptr1->flight_dep) < (lptr2->flight_dep) : t==3 ? (lptr1->flight_stay) < (lptr2->flight_stay) : t==4 ? (lptr1->flight_id) < (lptr2->flight_id) : t==5 ? (lptr1->flight_delay) < (lptr2->flight_delay) : strcmp((lptr1->flight_name),(lptr2->flight_name)) < 0 )
        {
            result = lptr1;
            p = p->next;
        }
        else
        {
            result = lptr2;
            q = q->next;
        }
        tail = result;
        while((p != NULL)&&(q != NULL))
        {
            if(t==1 ? (p->flight_arr) < (q->flight_arr) : t==2 ? (p->flight_dep) < (q->flight_dep) : t==3 ? (p->flight_stay) < (q->flight_stay) : t==4 ? (p->flight_id) < (q->flight_id) : t==5 ? (p->flight_delay) < (q->flight_delay) : strcmp((p->flight_name),(q->flight_name)) < 0 )
            {
                tail = tail->next = p;
                p = p->next;
            }
            else
            {
                tail = tail->next = q;
                q = q->next;
            }
        }
        if(p != NULL)
        {
            tail->next = p;
        }
        else
        {
            tail->next = q;
        }
    }
    return result;
}

//divide function
struct flight_record *divide(struct flight_record *lptr)
{
    struct flight_record *slow,*fast,*result;
    slow = lptr;
    fast = lptr->next->next;
    while(fast != NULL)
    {
        slow = slow->next;
        fast = fast->next;
        if(fast != NULL)
        {
            fast = fast->next;
        }
    }
    result = slow->next;
    slow->next = NULL;
    return result;
}

//sort function
struct flight_record *sort(struct flight_record *lptr,int p)
{
    struct flight_record *head,*temp;
    head = lptr;
    if((head != NULL)&&(head->next != NULL))
    {
        temp = divide(lptr);
        lptr = sort(lptr,p);
        temp = sort(temp,p);
        head = merge(lptr,temp,p);
    }
    return head;
}

void getSortedOnArrivalTime(struct flight_record *lptr)
{
    lptr=sort(lptr,1);
    flight=lptr;
}

void getSortedOnDepartureTime(struct flight_record *lptr)
{
    lptr=sort(lptr,2);
    flight=lptr;
}

void getSortedOnStayTime(struct flight_record *lptr)
{
    lptr=sort(lptr,3);
    flight=lptr;
}

struct flight_record *getClassList(struct flight_record *lptr,char str[7])
{
    struct flight_record *nptr,*cptr;
    nptr=NULL;
    while(lptr != NULL)
    {
        if(strcmp(lptr->flight_class,str) == 0)
        {
            cptr=(struct flight_record*)malloc(sizeof(struct flight_record));
            strcpy(cptr->flight_name,lptr->flight_name);
            cptr->flight_id = lptr->flight_id;
            cptr->flight_arr = lptr->flight_arr;
            cptr->flight_dep = lptr->flight_dep;
            cptr->flight_cap = lptr->flight_cap;
            strcpy(cptr->flight_status,lptr->flight_status);
            strcpy(cptr->flight_class,lptr->flight_class);
            cptr->flight_stay = lptr->flight_stay;
            cptr->next=nptr;
            nptr=cptr;
        }
        lptr=lptr->next;
    }
    return nptr;
}
void UpdateFlightStatus(struct flight_record *jptr,struct flightupdate *nptr)
{
    printf("\nBefore Updating List : \n");
    print(flight);
    struct flight_record *aptr;
    struct flightupdate *bptr;
    aptr=jptr;
    bptr=nptr;
    while(aptr!=NULL)
    {
        strcpy(aptr->flight_status,bptr->status);
        if(strcmp(bptr->status,"DELAY") == 0)
        {
            aptr->flight_delay = bptr->fdeltime;
        }
        else if(strcmp(bptr->status,"PROMOTED") == 0)
        {
            strcpy(aptr->flight_class,bptr->promote_status);
        }
        aptr=aptr->next;
    }
    flight=jptr;
    printf("\nAfter Updating list :\n");
    flight=sort(flight,4);
    flight=sort(flight,6);
    print(flight);
}

struct flight_record *list_unique(struct flight_record *lptr)
{
    struct flight_record *dptr,*tptr,*rptr,*cptr,*min,*sptr;
    lptr=sort(lptr,5);
    lptr=sort(lptr,4);
    dptr=lptr;
    rptr=lptr;
    int flag=0;
    while( dptr != NULL && dptr->next != NULL && flag==0)
    {
        if(dptr->flight_id == (dptr->next)->flight_id)
        {
            tptr=(dptr->next)->next;
            if(tptr==NULL)
            {
                dptr->next = NULL;
                flag=1;
            }
            if(flag==0)
                dptr->next=tptr;
        }
        else
            sptr=dptr;
        dptr= dptr->next;
    }
    flag=0;
    lptr=sort(lptr,5);
    lptr=sort(lptr,6);
    dptr=lptr;
    while( dptr != NULL && dptr->next != NULL && flag==0)
    {
        if(strcmp(dptr->flight_name,(dptr->next)->flight_name) == 0)
        {
            tptr=(dptr->next)->next;
            if(tptr==NULL)
            {
                dptr->next = NULL;
                flag=1;
            }
            if(flag==0)
                dptr->next=tptr;
        }
        else
            dptr= dptr->next;
    }
    lptr=sort(lptr,4);
    lptr=sort(lptr,5);
    return lptr;
}

int main()
{
        flight = NULL;
        uptr = NULL;
        printf("Enter flight details\n\n");
        char class1[]="VIP";
        char class2[]="VVIP";
        char class3[]="public";
        char status1[]="DELAY";
        char status2[]="ON_TIME";
        char status3[]="CANCELLED";
        char status4[]="PROMOTED";
    flight=InsertAtStart(flight,"Indigo",24001,125,1225,1345,class1,status2,0);
    flight=InsertAtStart(flight,"AirIndia",25949,190,1400,1635,class3,status1,0120);
    flight=InsertAtStart(flight,"Kingfisher",12412,240,2300,0045,class1,status3,0);
    flight=InsertAtStart(flight,"AirIndia",3434,130,935,1540,class2,status1,0045);
    flight=InsertAtStart(flight,"GoAir",12987,350,2215,1435,class3,status2,0);
    flight=InsertAtStart(flight,"AirAsia",56412,100,1630,1947,class1,status3,0);
    flight=InsertAtStart(flight,"TruJet",141187,40,1700,1745,class2,status4,0);
        print(flight);
    printf("\n");
        int option;
        while(1) {
            printf("Enter :\n");
            printf("Enter 0 to printf record\n";)
            printf("1 to insert details of a new flight or update details of an existing flight\n");
            printf("2 to delete a flight record\n");
            printf("3 to get number of flights in the list\n");
            printf("4 to know whether the list is empty or not\n");
            printf("5 to know whether the list is full or not\n");
            printf("6 to get the flight with longest stay\n");
            printf("7 to sort records on Arrival time\n");
            printf("8 to sort records on Departure time\n");
            printf("9 to sort records on Stay time\n");
            printf("10 to get lists based on class\n");
            printf("11 to UpdateFlightStatus\n");
            printf("12 to delete duplicate nodes\n");
            scanf("%d",&option);
            printf("\n\n");
            switch(option)
                {
            case 0:
                {
                    print(flight);
            }
            break;
            case 1:
                {
                    printf("Enter flight name : ");
                    char newname[100];
                    scanf("%s",newname);
                    printf("Enter flight id : ");
                    int newid;
                    scanf("%d",&newid);
                    printf("Enter arrival time : ");
                    int arrtime;
                    scanf("%d",&arrtime);
                    printf("Enter departure time : ");
                    int deptime;
                    scanf("%d",&deptime);
                    printf("Enter delay time : ");
                    int delaytime;
                    scanf("%d",&delaytime);
                    printf("Enter capacity : ");
                    int flicap;
                    scanf("%d",&flicap);
                    printf("Enter status of flight : ");
                    char fstatus[100];
                    scanf("%s",fstatus);
                    printf("Enter flight class : ");
                    char newclass[100];
                    scanf("%s",newclass);
                    int a=insert(newname,newid,flicap,arrtime,deptime,newclass,fstatus,delaytime);
                    if(a==1)
                        {
                        printf("Inserted or updated flight status successfully!!\n\n");
                }
                else
                    printf("Insertion not done due to insufficient memory!!\n\n");
            }
            break;
        case 2:
        {
            printf("Enter the Id of the flight to be deleted : ");
            int delId;
            scanf("%d",&delId);
            struct flight_record *del;
            del=flight;
            delete_rec(del,delId);
        }
        break;
        case 3:
        {
            int count;
            count=getNumFlights(flight);
            printf("Number of flights in the list : %d\n\n",count);
        }
        break;
        case 4:
        {
            if(isEmpty(flight) == 1)
            {
                printf("The list is empty\n\n");
            }
            else
            {
                printf("The list is not empty\n\n");
            }
        }
        break;
        case 5:
        {
            if(isFull(flight) == 1)
            {
                printf("The list is full\n\n");
            }
            else
            {
                printf("The list is not full");
            }
        }
        break;
        case 6:
        {
            printf("The list after sorting using arrival time :\n\n");
            geFlightWithtLongeststay(flight);
        }
        break;
        case 7:
        {
            printf("The list after sorting using departure time :\n\n");
            getSortedOnArrivalTime(flight);
            print(flight);
        }
        break;
        case 8:
        {
            printf("The list after sorting using stay time :\n\n");
            getSortedOnDepartureTime(flight);
            print(flight);
        }
        break;
        case 9:
        {
            getSortedOnStayTime(flight);
            print(flight);
        }
        break;
        case 10:
        {
            struct flight_record *vip,*vvip,*pub;
            vip=getClassList(flight,"VIP");
            vvip=getClassList(flight,"VVIP");
            pub=getClassList(flight,"public");
            print(vip);
            printf("\n\n\n");
            print(vvip);
            printf("\n\n\n");
            printf("The list after sorting using stay time :\n\n");
            print(pub);
        }
        break;
        case 11:
        {
            vptr=(struct flightupdate*)malloc(sizeof(struct flightupdate*));
            struct flight_record *mptr;
            mptr=flight;
            while(mptr != NULL)
            {
                strcpy(vptr->fname,mptr->flight_name);
                vptr->fid = mptr->flight_id;
                vptr->fdeltime = 0;
                strcpy(vptr->promote_status,"\0");
                printf("Enter status for the flight :\n");
                printf(" Name : %s\n Flight ID : %d\n",mptr->flight_name,mptr->flight_id);
                scanf("%s",vptr->status);
                if(strcmp(vptr->status,"DELAY") == 0)
                {
                    printf("Enter the delay time in 24 hrs format\n");
                    scanf("%d",&vptr->fdeltime);
                }
                else if(strcmp(vptr->status,"PROMOTED") == 0)
                {
                    printf("Original class of flight is : %s\nEnter the class to which we should promote : ",mptr->flight_class);
                    scanf("%s",vptr->promote_status);
                }
                vptr->next=uptr;
                uptr=vptr;
                mptr=mptr->next;
            }
            UpdateFlightStatus(flight,uptr);
        }
        break;
        case 12:
        {
            flight=list_unique(flight);
            printf("After removing duplicate entries :\n");
            print(flight);
        }
        break;
        }
    }
    return 0;
}


