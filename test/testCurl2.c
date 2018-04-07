#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <curl/curl.h>
#define POSTDATA "{\"username\":\"gailun\",\"password\":\"123123\"}"
int main(int argc, char *argv[]){
    CURL* curl = NULL;
    CURLcode res;
    curl = curl_easy_init();
    if(curl == NULL){
        return -1;
    }
    curl_easy_setopt(curl, CURLOPT_URL, "http://10.108.37.188:8090/");
    //更改curl为post请求
    curl_easy_setopt(curl, CURLOPT_POST, 1);

    //给post请求提供一些post数据
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTDATA);

    //向远程提交请求
    res = curl_easy_perform(curl);

    if(res != CURLE_OK){
        printf("perform error res = %d\n", res);
        return -1;
    }
    //处理服务器响应数据
    curl_easy_cleanup(curl);
    return 0;
}
