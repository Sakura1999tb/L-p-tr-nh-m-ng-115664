#include <stdio.h>
#include <tchar.h>
#include <winsock2.h>
#include <iostream>
#include <WS2TCPIP.H>
#pragma comment (lib,"ws2_32.lib")
using namespace std;

//----- Ham check Domain xem cho dung format khong----//
bool checkDomain(string Domain) {
    int i = 0;
    for (i = 0; i < Domain.size();i++) {
        char tmp = Domain.at(i);
        if (tmp != '.' && tmp != '-' && 0 <= tmp && tmp <= 9 && 'a' < tmp && tmp < 'z' && 'A' < tmp && tmp < 'Z') {
            return false;
        }
    }
    return true;
}
//------- End Ham check Domain -----------------------//




//----------------MAIN-------------------------//
int _tmain(int argc, _TCHAR* argv[])
{
    //-------------------//Bat dau khoi tao Winsock---------------------------//
    WSADATA SData;   
    int iResult = WSAStartup(0x0202, &SData);
    if (iResult != 0) {
        cout << "KHONG THE KHOI DONG WINSOCK";
        return 1;
    }                
    //------------------//Ket thuc khoi tao Winsock---------------------------//

    //-----------------Bat dau phan giai ten mien ------------------------//
    int lenDN = 0;      //  Khai bao bien chi do dai ten mien
    string DomainName; //   Khai bao bien ten mien
    cout << "Nhap vao ten mien \n";
    cin >> DomainName;
    if (checkDomain(DomainName)) {                  //Check Domain
        const char* DN = DomainName.c_str();        //Chuyen sang kieu const char* de co the su dung vao ham getaddrinfo
        addrinfo* info;                             //Khai bao con tro info luu tru du lieu sau khi phan giai
        int ret = getaddrinfo(DN, "http", NULL, &info);
        if (ret == 0){
            while (info->ai_next != NULL) {
                SOCKADDR_IN addr;
                memcpy(&addr, info->ai_addr, info->ai_addrlen);      //Neu phan giai thanh cong thi sao chep dia chi vao bien addr
                char ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &(addr.sin_addr), ip, INET_ADDRSTRLEN);
                cout << "IP = " << ip <<"\n";                       // In ra dia chi IP
                info = info->ai_next;
            }
        }
        else {
            cout << "Khong phan giai duoc ten mien";
        }
    }
    else {
        cout << "Ten mien khong phu hop";
    }
 
    WSACleanup(); // Ket thuc phien lam viec cua WS
    return 0;
}