#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;
int registers[16];//registers[15]=pc,registers[14]=link register
int memory[100];
int latency[11];

int main()
{ 
    string x;
    string a[2000];//stores each line in an array element 
    int label_index[2000];
    string label_name[2000];
    int i=0;
    int count=0;//len of labels array
    int flag1=0;//to check the labels errors
        std::regex add1 ("([[:space:]]*)(a|A)(d|D)(d|D)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)");
        std::regex add2 ("([[:space:]]*)(a|A)(d|D)(d|D)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(\\#)([[:space:]]*)([[:digit:]])([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:space:]]*)");
        std::regex sub1 ("([[:space:]]*)(s|S)(u|U)(b|B)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)");
        std::regex sub2 ("([[:space:]]*)(s|S)(u|U)(b|B)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(\\#)([[:space:]]*)([[:digit:]])([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:space:]]*)");
        std::regex mul ("([[:space:]]*)(m|M)(u|U)(l|L)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)");
        std::regex mov1 ("([[:space:]]*)(m|M)(o|O)(v|V)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)");
        std::regex mov2 ("([[:space:]]*)(m|M)(o|O)(v|V)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(\\#)([[:space:]]*)([[:digit:]])([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:space:]]*)");
        std::regex cmp1 ("([[:space:]]*)(c|C)(m|M)(p|P)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)");
        std::regex cmp2 ("([[:space:]]*)(c|C)(m|M)(p|P)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(\\#)([[:space:]]*)([[:digit:]])([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:space:]]*)");
        std::regex ldr1 ("([[:space:]]*)(l|L)(d|D)(r|R)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(\\[)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(\\#)([[:space:]]*)([[:digit:]])([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:space:]]*)(\\])([[:space:]]*)");
        std::regex ldr2 ("([[:space:]]*)(l|L)(d|D)(r|R)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(\\[)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\])([[:space:]]*)(\\,)([[:space:]]*)(\\#)([[:space:]]*)([[:digit:]])([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:space:]]*)");
        std::regex ldr3 ("([[:space:]]*)(l|L)(d|D)(r|R)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(\\[)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\])([[:space:]]*)");
        std::regex str2 ("([[:space:]]*)(s|S)(t|T)(r|R)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(\\[)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\])([[:space:]]*)(\\,)([[:space:]]*)(\\#)([[:space:]]*)([[:digit:]])([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:space:]]*)");
        std::regex str1 ("([[:space:]]*)(s|S)(t|T)(r|R)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(\\[)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(\\#)([[:space:]]*)([[:digit:]])([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:digit:]]?)([[:space:]]*)(\\])([[:space:]]*)");
        std::regex str3 ("([[:space:]]*)(s|S)(t|T)(r|R)([[:space:]]+)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\,)([[:space:]]*)(\\[)([[:space:]]*)(r|R)([0-9]|1[0-5])([[:space:]]*)(\\])([[:space:]]*)");
        std::regex b("([[:space:]]*)(b|B)([[:space:]]+)([a-zA-Z])([a-zA-Z0-9]*)([[:space:]]*)");
        std::regex bne("([[:space:]]*)(b|B)(n|N)(e|E)([[:space:]]+)([a-zA-Z])([a-zA-Z0-9]*)([[:space:]]*)");
        std::regex bge("([[:space:]]*)(b|B)(g|G)(e|E)([[:space:]]+)([a-zA-Z])([a-zA-Z0-9]*)([[:space:]]*)");    
        std::regex bl("([[:space:]]*)(b|B)(l|L)([[:space:]]+)([a-zA-Z])([a-zA-Z0-9]*)([[:space:]]*)");    
        std::regex end("([[:space:]]*)(\\.)(e|E)(n|N)(d|D)([[:space:]]*)");
        std::regex exits("([[:space:]]*)(s|S)(w|W)(i|I)([[:space:]]+)(0x11)([[:space:]]*)");
        std::regex replacespace("([[:space:]]*)");
        std::regex labelmatch ("([[:space:]]*)([a-zA-Z])([a-zA-Z0-9]*)(\\:)([[:space:]]*)(.*)");
        std::regex labelreplace ("([[:space:]]*)([a-zA-Z])([a-zA-Z0-9]*)([[:space:]]*)(\\:)");
        std::regex ladd ("([[:space:]]*)(a|A)(d|D)(d|D)([[:space:]]+)(=)([[:space:]]+)([[:digit:]]+)(\\;)");
        std::regex lsub ("([[:space:]]*)(s|S)(u|U)(b|B)([[:space:]]+)(=)([[:space:]]+)([[:digit:]]+)(\\;)");
        std::regex lmul ("([[:space:]]*)(m|M)(u|U)(l|L)([[:space:]]+)(=)([[:space:]]+)([[:digit:]]+)(\\;)");
        std::regex lbne ("([[:space:]]*)(b|B)(n|N)(e|E)([[:space:]]+)(=)([[:space:]]+)([[:digit:]]+)(\\;)");
        std::regex lb ("([[:space:]]*)(b|B)([[:space:]]+)(=)([[:space:]]+)([[:digit:]]+)(\\;)");
        std::regex lbge ("([[:space:]]*)(b|B)(g|G)(e|E)([[:space:]]+)(=)([[:space:]]+)([[:digit:]]+)(\\;)");
        std::regex lmov ("([[:space:]]*)(m|M)(o|O)(v|V)([[:space:]]+)(=)([[:space:]]+)([[:digit:]]+)(\\;)");
        std::regex lcmp ("([[:space:]]*)(c|C)(m|M)(p|P)([[:space:]]+)(=)([[:space:]]+)([[:digit:]]+)(\\;)");
        std::regex lbl ("([[:space:]]*)(b|B)(l|L)([[:space:]]+)(=)([[:space:]]+)([[:digit:]]+)(\\;)");
        std::regex lstr ("([[:space:]]*)(s|S)(t|T)(r|R)([[:space:]]+)(=)([[:space:]]+)([[:digit:]]+)(\\;)");
        std::regex lldr ("([[:space:]]*)(l|L)(d|D)(r|R)([[:space:]]+)(=)([[:space:]]+)([[:digit:]]+)(\\;)");

    //Initializing registers values to 0
    for(int j=0;j<16;j++)
    registers[j]=0;

    for(int j=0;j<100;j++)
    {memory[j]=0;label_index[j]=-1;label_name[j]="";}
    
    for(int j=0;j<11;j++)
    latency[j]=0;

    ifstream inFile;
    inFile.open("./input.txt");
    ofstream outfile ("output.txt");
    
    ifstream inFilelatency;
    inFilelatency.open("./latency.txt");

    //Checking if the file is opened or not
    if (!inFile) 
    {
        cerr << "Unable to open file input.txt";
        exit(1);   // call system to stop
    }
    

    //Checking if the file is opened or not
    if (!inFilelatency) 
    {
        cerr << "Unable to open file latency.txt";
        exit(1);   // call system to stop
    }
    
    while(getline(inFile,x))
    { 
      a[i]=x;
      if(std::regex_match(a[i],end))
      break;
      if(std::regex_match(a[i],labelmatch))
      { flag1=0;      
        //cout<<"IN label match"<<endl;
        std::smatch m;
        std::regex replace("([[:space:]]*)(\\:)");
        std::regex_search (a[i],m,labelreplace);
        string s=m.str();
        s=std::regex_replace (s,replace,"");
        s=std::regex_replace (s,replacespace,"");
        //cout<<label_name[count]<<endl;
        for(int z=0;z<count;z++)
        {
            if(label_name[z].compare(s)==0)
            {
                flag1=1;
                cout<<"Error in the line:"<<i+1<<endl;
                break;
            }
        }
        if(flag1==1)
        break;
        label_name[count]=s;
        label_index[count]=i;
        count++;
        if (!std::regex_match(m.suffix().str(),replacespace))
        {
          a[i]=m.suffix().str();
          //cout<<a[i]<<endl;
        }
      }
      //cout<<a[i]<<endl;
      i++;
    }
    i=0;

    while(getline(inFilelatency,x))
    {
        std::string s1=x;
        std::regex e ("[[:digit:]]+");
        std::smatch m;
        std::regex_search (s1,m,e);
        int number=std::stoi(m.str());
        if(std::regex_match(s1,ladd))
        latency[0]=number;
        else if(std::regex_match(s1,lsub))
        latency[1]=number;
        else if(std::regex_match(s1,lmul))
        latency[2]=number;
        else if(std::regex_match(s1,lbne))
        latency[3]=number;
        else if(std::regex_match(s1,lb))
        latency[4]=number;
        else if(std::regex_match(s1,lbge))
        latency[5]=number;
        else if(std::regex_match(s1,lmov))
        latency[6]=number;
        else if(std::regex_match(s1,lcmp))
        latency[7]=number;
        else if(std::regex_match(s1,lbl))
        latency[8]=number;
        else if(std::regex_match(s1,lstr))
        latency[9]=number;
        else if(std::regex_match(s1,lldr))
        latency[10]=number;
    }

int tl=0,ti=0;//tl-total latency,ti=total instruction count
 
if(flag1==0)
{
    while(!std::regex_match(a[i],exits))
    {     
        
        //Addition type 1
        if (std::regex_match (a[i],add1))
        {   
            ti++;
            tl+=latency[0];
            //std::cout << "string addobject1 matched\n";
            int op[3];
            int count=0;
            std::string s=a[i];
            std::smatch m;
            std::regex e ("[[:digit:]]+");   // matches digits

            //std::cout << "Target sequence: " << s << std::endl;
            //std::cout << "The following matches were found:" << std::endl;

            while (std::regex_search (s,m,e)) 
            {
                //std::cout << "Pattern found was: " << m.str() << std::endl;
                op[count]=std::stoi(m.str());
                //cout<<"Op"<<count<<"="<<op[count]<<endl;
                count++;
                s = m.suffix().str();
            }
            registers[op[0]]=registers[op[1]]+registers[op[2]];
            //cout<<"Reg"<<op[0]<<"="<<registers[op[0]]<<endl;
            //cout<<"Reg"<<op[1]<<"="<<registers[op[1]]<<endl;
            //cout<<"Reg"<<op[2]<<"="<<registers[op[2]]<<endl;
        }
        //Addition type 2
        else if (std::regex_match (a[i],add2))
        {    
            ti++;
            tl+=latency[0];
            //std::cout << "string addobject2 matched\n";
            int op[3];
            int count=0;            
            std::string s=a[i];
            std::smatch m;
            std::regex e ("[[:digit:]]+");   // matches digits

            //std::cout << "Target sequence: " << s << std::endl;
            //std::cout << "The following matches were found:" << std::endl;

            while (std::regex_search (s,m,e)) 
            {
                //std::cout << "Pattern found was: " << m.str() << std::endl;
                op[count]=std::stoi(m.str());
                //cout<<"Op"<<count<<"="<<op[count]<<endl;
                count++;
                s = m.suffix().str();
            }
            registers[op[0]]=registers[op[1]]+op[2];
            //cout<<"Reg"<<op[0]<<"="<<registers[op[0]]<<endl;
            //cout<<"Reg"<<op[1]<<"="<<registers[op[1]]<<endl;
        }
        //Move instruction type 1.
        else if(std::regex_match (a[i],mov1))
        {
            ti++;
            tl+=latency[6];
            //std::cout << "string movobject1 matched\n";
            int op[2];
            int count=0;
            std::string s=a[i];
            std::smatch m;
            std::regex e ("[[:digit:]]+");   // matches digits

            //std::cout << "Target sequence: " << s << std::endl;
            //std::cout << "The following matches were found:" << std::endl;

            while (std::regex_search (s,m,e)) 
            {
                //std::cout << "Pattern found was: " << m.str() << std::endl;
                op[count]=std::stoi(m.str());
                //cout<<"Op"<<count<<"="<<op[count]<<endl;
                count++;
                s = m.suffix().str();
            }
            registers[op[0]]=registers[op[1]];
            //cout<<"Reg"<<op[0]<<"="<<registers[op[0]]<<endl;
            //cout<<"Reg"<<op[1]<<"="<<registers[op[1]]<<endl;
        }
        //Move instruction type 2.
        else if(std::regex_match (a[i],mov2))
        {
            ti++;
            tl+=latency[6];
            //std::cout << "string movobject2 matched\n";
            int op[2];
            int count=0;
            std::string s=a[i];
            std::smatch m;
            std::regex e ("[[:digit:]]+");   // matches digits

            //std::cout << "Target sequence: " << s << std::endl;
            //std::cout << "The following matches were found:" << std::endl;

            while (std::regex_search (s,m,e)) 
            {
                //std::cout << "Pattern found was: " << m.str() << std::endl;
                op[count]=std::stoi(m.str());
                //cout<<"Op"<<count<<"="<<op[count]<<endl;
                count++;
                s = m.suffix().str();
            }
            registers[op[0]]=op[1];
            //cout<<"Reg"<<op[0]<<"="<<registers[op[0]]<<endl;
        }
        //Substraction type 1.
        else if (std::regex_match (a[i],sub1))
        {   
            ti++;
            tl+=latency[1];
            //std::cout << "string subobject1 matched\n";
            int op[3];
            int count=0;
            std::string s=a[i];
            std::smatch m;
            std::regex e ("[[:digit:]]+");   // matches digits

            //std::cout << "Target sequence: " << s << std::endl;
            //std::cout << "The following matches were found:" << std::endl;

            while (std::regex_search (s,m,e)) 
            {
                //std::cout << "Pattern found was: " << m.str() << std::endl;
                op[count]=std::stoi(m.str());
                //cout<<"Op"<<count<<"="<<op[count]<<endl;
                count++;
                s = m.suffix().str();
            }
            registers[op[0]]=registers[op[1]]-registers[op[2]];
            //cout<<"Reg"<<op[0]<<"="<<registers[op[0]]<<endl;
            //cout<<"Reg"<<op[1]<<"="<<registers[op[1]]<<endl;
            //cout<<"Reg"<<op[2]<<"="<<registers[op[2]]<<endl;
        }
        //Subtraction type 2
        else if (std::regex_match (a[i],sub2))
        {   
            ti++;
            tl+=latency[1]; 
            //std::cout << "string subobject2 matched\n";
            int op[3];
            int count=0;            
            std::string s=a[i];
            std::smatch m;
            std::regex e ("[[:digit:]]+");   // matches digits

           // std::cout << "Target sequence: " << s << std::endl;
           // std::cout << "The following matches were found:" << std::endl;

            while (std::regex_search (s,m,e)) 
            {
                //std::cout << "Pattern found was: " << m.str() << std::endl;
                op[count]=std::stoi(m.str());
                //cout<<"Op"<<count<<"="<<op[count]<<endl;
                count++;
                s = m.suffix().str();
            }
            registers[op[0]]=registers[op[1]]-op[2];
            //cout<<"Reg"<<op[0]<<"="<<registers[op[0]]<<endl;
            //cout<<"Reg"<<op[1]<<"="<<registers[op[1]]<<endl;
        }
        //Multiplication.
        else if (std::regex_match (a[i],mul))
        {   
            ti++;
            tl+=latency[2];
            //std::cout << "string addobject1 matched\n";
            int op[3];
            int count=0;
            std::string s=a[i];
            std::smatch m;
            std::regex e ("[[:digit:]]+");   // matches digits

            //std::cout << "Target sequence: " << s << std::endl;
            //std::cout << "The following matches were found:" << std::endl;

            while (std::regex_search (s,m,e)) 
            {
                //std::cout << "Pattern found was: " << m.str() << std::endl;
                op[count]=std::stoi(m.str());
                //cout<<"Op"<<count<<"="<<op[count]<<endl;
                count++;
                s = m.suffix().str();
            }
            registers[op[0]]=registers[op[1]]*registers[op[2]];
            //cout<<"Reg"<<op[0]<<"="<<registers[op[0]]<<endl;
            //cout<<"Reg"<<op[1]<<"="<<registers[op[1]]<<endl;
            //cout<<"Reg"<<op[2]<<"="<<registers[op[2]]<<endl;
        }
        //Compare instruction type 1.
        else if(std::regex_match (a[i],cmp1))
        { 
            ti++;
            tl+=latency[7];
          if((std::regex_match (a[i+1],bge) || std::regex_match (a[i+1],bne)))
          {  
            //std::cout << "string cmpobject1 matched\n";
            int op[2];
            int count=0;
            std::string s=a[i];
            std::smatch m;
            std::regex e ("[[:digit:]]+");   // matches digits

            //std::cout << "Target sequence: " << s << std::endl;
            //std::cout << "The following matches were found:" << std::endl;

            while (std::regex_search (s,m,e)) 
            {
                //std::cout << "Pattern found was: " << m.str() << std::endl;
                op[count]=std::stoi(m.str());
                //cout<<"Op"<<count<<"="<<op[count]<<endl;
                count++;
                s = m.suffix().str();
            }
            if((registers[op[0]]>registers[op[1]] || registers[op[0]]==registers[op[1]]) || registers[op[0]]!=registers[op[1]])
            {         //cout<<"-----------------"<<i<<endl;
                      //branch type -bne
                      if(std::regex_match (a[i+1],bne))
                      {
                          ti++;
                          tl+=latency[3];
                      }
                      if (std::regex_match (a[i+1],bne) && registers[op[0]]!=registers[op[1]])
                      {   
                          i++;
                          //std::cout << "bne matched\n";
                          std::string s=a[i];
                          std::smatch m1;
                          std::regex e ("([[:space:]]*)([bne])([[:space:]]+)");   // matches digits
                          std::regex_search (s,m1,e);
                          //std::cout << "Target sequence: " << s << std::endl;
                          //std::cout << "The following matches were found:" << std::endl;
                         // std::cout << "Pattern found was: " << m1.str() << std::endl;
                          s = m1.suffix().str();
                          s=std::regex_replace (s,replacespace,"");
                          //cout<<"remaining label name="<<s<<endl;
                          int flag=0;
                          for(int k=0;k<count;k++)
                          {
                              if(s.compare(label_name[k])==0)
                              {
                                i=label_index[k]-1;
                                flag=1;
                                //cout<<"compared done"<<endl;
                                break;
                              }
                          }
                          if (flag==0)
                          {
                            cout<<"Invalid label name found in line:"<<(i+1)<<endl;  
                            break;
                          }
                      }   
                      //branch type -bge
                      if(std::regex_match (a[i+1],bge))
                      {
                          ti++;
                          tl+=latency[5];
                      }
                      else if (std::regex_match (a[i+1],bge) && (registers[op[0]]>registers[op[1]] || registers[op[0]]==registers[op[1]]))
                      {   
                          i++;
                          //std::cout << "bge matched\n";
                          std::string s=a[i];
                          std::smatch m1;
                          std::regex e ("([[:space:]]*)([bge])([[:space:]]+)");   // matches digits
                          std::regex_search (s,m1,e);
                          //std::cout << "Target sequence: " << s << std::endl;
                         // std::cout << "The following matches were found:" << std::endl;
                         // std::cout << "Pattern found was: " << m1.str() << std::endl;
                          s = m1.suffix().str();
                          s=std::regex_replace (s,replacespace,"");
                          //cout<<"remaining label name="<<s<<endl;
                          int flag=0;
                          for(int k=0;k<count;k++)
                          {
                              if(s.compare(label_name[k])==0)
                              {
                                i=label_index[k]-1;
                                flag=1;
                               // cout<<"compared done"<<endl;
                                break;
                              }
                          }
                          if (flag==0)
                          {
                            cout<<"Invalid label name found in line:"<<(i+1)<<endl;  
                            break;
                          }
                      }
                      else 
                      i++;            
              }
            else 
            i++;
        }
        else
        {
        cout<<"Error found in line:"<<(i+2)<<endl;  
        break;
        }
      }
        //Compare instruction type 2.
        else if(std::regex_match (a[i],cmp2))
        {
            ti++;
            tl+=latency[7];
          if((std::regex_match (a[i+1],bge) || std::regex_match (a[i+1],bne)))
          {
            //std::cout << "string cmpobject2 matched\n";
            int op[2];
            int count=0;
            std::string s=a[i];
            std::smatch m;
            std::regex e ("[[:digit:]]+");   // matches digits

            //std::cout << "Target sequence: " << s << std::endl;
            //std::cout << "The following matches were found:" << std::endl;

            while (std::regex_search (s,m,e)) 
            {
                //std::cout << "Pattern found was: " << m.str() << std::endl;
                op[count]=std::stoi(m.str());
                //cout<<"Op"<<count<<"="<<op[count]<<endl;
                count++;
                s = m.suffix().str();
            }
              if((registers[op[0]]>op[1] || registers[op[0]]==op[1]) || registers[op[0]]!=op[1])
            {         //cout<<"-----------------"<<i<<endl;
                      //branch type -bne
                      if(std::regex_match (a[i+1],bne))
                      {
                          ti++;
                          tl+=latency[3];
                      }
                      
                      if (std::regex_match (a[i+1],bne) && registers[op[0]]!=op[1])
                      {   
                          i++;
                          //std::cout << "bne matched\n";
                          std::string s=a[i];
                          std::smatch m1;
                          std::regex e ("([[:space:]]*)([bne])([[:space:]]+)");   // matches digits
                          std::regex_search (s,m1,e);
                          //std::cout << "Target sequence: " << s << std::endl;
                          //std::cout << "The following matches were found:" << std::endl;
                          //std::cout << "Pattern found was: " << m1.str() << std::endl;
                          s = m1.suffix().str();
                          s=std::regex_replace (s,replacespace,"");
                          //cout<<"remaining label name="<<s<<endl;
                          int flag=0;
                          for(int k=0;k<count;k++)
                          {
                              if(s.compare(label_name[k])==0)
                              {
                                i=label_index[k]-1;
                                flag=1;
                                //cout<<"compared done"<<endl;
                                break;
                              }
                          }
                          if (flag==0)
                          {
                            cout<<"Invalid label name found in line:"<<(i+1)<<endl;  
                            break;
                          }
                      }   
                      if(std::regex_match (a[i+1],bge))
                      {
                          ti++;
                          tl+=latency[5];
                      }
                      //branch type -bge
                      else if (std::regex_match (a[i+1],bge) && (registers[op[0]]>op[1] || registers[op[0]]==op[1]))
                      {   
                          i++;
                         // std::cout << "bge matched\n";
                          std::string s=a[i];
                          std::smatch m1;
                          std::regex e ("([[:space:]]*)([bge])([[:space:]]+)");   // matches digits
                          std::regex_search (s,m1,e);
                          //std::cout << "Target sequence: " << s << std::endl;
                          //std::cout << "The following matches were found:" << std::endl;
                          //std::cout << "Pattern found was: " << m1.str() << std::endl;
                          s = m1.suffix().str();
                          s=std::regex_replace (s,replacespace,"");
                          //cout<<"remaining label name="<<s<<endl;
                          int flag=0;
                          for(int k=0;k<count;k++)
                          {
                              if(s.compare(label_name[k])==0)
                              {
                                i=label_index[k]-1;
                                flag=1;
                                //cout<<"compared done"<<endl;
                                break;
                              }
                          }
                          if (flag==0)
                          {
                            cout<<"Invalid label name found in line:"<<(i+1)<<endl;  
                            break;
                          }
                      }
                      else 
                      i++;            
              }
            else 
            i++;
        }
            else
            {
            cout<<"Error found in line:"<<(i+2)<<endl;  
            break;
            }
        }
        //ldr1,ldr2 instruction
        else if (std::regex_match (a[i],ldr1) || std::regex_match (a[i],ldr2))
        {   
            ti++;
            tl+=latency[10]; 
            //std::cout << "string ldrobject matched\n";
            int op[3];
            int count=0;            
            std::string s=a[i];
            std::smatch m;
            std::regex e ("[[:digit:]]+");   // matches digits

            //std::cout << "Target sequence: " << s << std::endl;
            //std::cout << "The following matches were found:" << std::endl;

            while (std::regex_search (s,m,e)) 
            {
                std::cout << "Pattern found was: " << m.str() << std::endl;
                op[count]=std::stoi(m.str());
                cout<<"Op"<<count<<"="<<op[count]<<endl;
                count++;
                s = m.suffix().str();
            }
            registers[op[0]]=memory[registers[op[1]]+op[2]];
            //cout<<"Reg"<<op[0]<<"="<<registers[op[0]]<<endl;
        }
         //ldr3 instruction.
        else if(std::regex_match (a[i],ldr3))
        {
            ti++;
            tl+=latency[10]; 
            //std::cout << "string ldrobject3 matched\n";
            int op[2];
            int count=0;
            std::string s=a[i];
            std::smatch m;
            std::regex e ("[[:digit:]]+");   // matches digits

            //std::cout << "Target sequence: " << s << std::endl;
            //std::cout << "The following matches were found:" << std::endl;

            while (std::regex_search (s,m,e)) 
            {
                //std::cout << "Pattern found was: " << m.str() << std::endl;
                op[count]=std::stoi(m.str());
                //cout<<"Op"<<count<<"="<<op[count]<<endl;
                count++;
                s = m.suffix().str();
            }
            registers[op[0]]=memory[registers[op[1]]];
            //cout<<"Reg"<<op[0]<<"="<<registers[op[0]]<<endl;
        }
        //str1,str2 instruction
        else if (std::regex_match (a[i],str1) || std::regex_match (a[i],str2))
        {   
            ti++;
            tl+=latency[9];  
            //std::cout << "string strobject matched\n";
            int op[3];
            int count=0;            
            std::string s=a[i];
            std::smatch m;
            std::regex e ("[[:digit:]]+");   // matches digits

            //std::cout << "Target sequence: " << s << std::endl;
            //std::cout << "The following matches were found:" << std::endl;

            while (std::regex_search (s,m,e)) 
            {
                //std::cout << "Pattern found was: " << m.str() << std::endl;
                op[count]=std::stoi(m.str());
                //cout<<"Op"<<count<<"="<<op[count]<<endl;
                count++;
                s = m.suffix().str();
            }
            memory[registers[op[1]]+op[2]]=registers[op[0]];
            //cout<<"memory"<<registers[op[1]]+op[2]<<"="<<memory[registers[op[1]]+op[2]]<<endl;
        }
        //str3 instruction.
        else if(std::regex_match (a[i],str3))
        {
            ti++;
            tl+=latency[9]; 
            //std::cout << "string strobject3 matched\n";
            int op[2];
            int count=0;
            std::string s=a[i];
            std::smatch m;
            std::regex e ("[[:digit:]]+");   // matches digits

            //std::cout << "Target sequence: " << s << std::endl;
            //std::cout << "The following matches were found:" << std::endl;

            while (std::regex_search (s,m,e)) 
            {
                //std::cout << "Pattern found was: " << m.str() << std::endl;
                op[count]=std::stoi(m.str());
                //cout<<"Op"<<count<<"="<<op[count]<<endl;
                count++;
                s = m.suffix().str();
            }
            memory[registers[op[1]]]=registers[op[0]];
            //cout<<"mem"<<registers[op[1]]<<"="<<memory[registers[op[1]]]<<endl;
        }
        //branch type 1-b
        else if (std::regex_match (a[i],b))
        {   
            ti++;
            tl+=latency[4]; 
            //std::cout << "string branch1 matched\n";
            std::string s=a[i];
            std::smatch m;
            std::regex e ("([[:space:]]*)([b])([[:space:]]+)");   // matches digits
            std::regex_search (s,m,e);
            //std::cout << "Target sequence: " << s << std::endl;
            //std::cout << "The following matches were found:" << std::endl;
            //std::cout << "Pattern found was: " << m.str() << std::endl;
            s = m.suffix().str();
            s=std::regex_replace (s,replacespace,"");
            int flag=0;
            for(int k=0;k<count;k++)
            {
                if(s.compare(label_name[k])==0)
                {
                  i=label_index[k]-1;
                  flag=1;
                  //cout<<"compared done"<<endl;
                  break;
                }
            }
            if (flag==0)
            {
               cout<<"Invalid label name found in line:"<<(i+1)<<endl;  
               break;
            }
        }
        //branch type -bl
        else if (std::regex_match (a[i],bl))
        {   
            ti++;
            tl+=latency[8]; 
            //std::cout << "string bl matched\n";   
            std::string s=a[i];
            std::smatch m;
            std::regex e ("([[:space:]]*)([bl])([[:space:]]+)");   // matches digits
            std::regex_search (s,m,e);
            //std::cout << "Target sequence: " << s << std::endl;
            //std::cout << "The following matches were found:" << std::endl;
            //std::cout << "Pattern found was: " << m.str() << std::endl;
            s = m.suffix().str();
            s=std::regex_replace (s,replacespace,"");
            int flag=0;
            for(int k=0;k<count;k++)
            {
                if(s.compare(label_name[k])==0)
                {
                  registers[14]=i+1;
                  i=label_index[k]-1;              
                  flag=1;
                  //cout<<"compared done"<<endl;
                  break;
                }
            }
            if (flag==0)
            {
               cout<<"Invalid label name found in line:"<<(i+1)<<endl;  
               break;
            }
        }
        else if(std::regex_match (a[i],labelmatch))
        {
           // cout<<"label ignored"<<endl;
        }
        else if(std::regex_match(a[i],replacespace))
        {
           // cout<<"Blank line"<<endl;
        }
        else
        {
        cout<<"Error found in line:"<<(i+1)<<endl;  
        break; 
        }
        outfile << "=================================================================================" <<endl;
            registers[15]=4000+4*(i);
            outfile << "Instruction "<<i+1<<endl;
            outfile << "-----------------------" <<endl;
            outfile << "Register     |   Values" <<endl;
            outfile << "-----------------------" <<endl;
            for(int val=0;val<16;val ++)
            outfile <<"r"<<val<<"   \t\t"<< " | " <<"\t"<<registers[val]<<"\t"<<endl;
            outfile << "-----------------------" <<endl; 
            outfile << "Number of cycles:"<<tl<<endl;
            outfile << "-----------------------" <<endl;
            outfile << "Memory(size=100 words)" <<endl;
            outfile << "-----------------------" <<endl;
            for(int val=0;val<5;val++)
            {
                for(int valj=0;valj<20;valj++)
                outfile<<"[M"<<20*val+valj<<"]"<<memory[10*val+valj]<<"   ";
                outfile<<endl;
            }
        outfile << "=================================================================================" <<endl;
        i++;
    }
}
    cout<<"Program complied-Check output.txt"<<endl;
    outfile << "CPI:" <<(float(tl)/ti)<<endl;
    //outfile << "ti:" <<(ti)<<endl;
    inFile.close();
    outfile.close();
    return 0;
}