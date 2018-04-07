#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <curl/curl.h>
#define POSTDATA "{\"username\":\"gailun\",\"password\":\"123123\"}"
/**
 * @brief 用来处理服务器返回的回调函数业务
 * @param ptr 就是服务器数据的首地址
 * @param size  从服务器获取数据的每帧的长度
 * @param nmemb 多少个帧
 * @param userdata  用户提供的形参
 * 
 * @returns
 *      已经处理服务器返回数据的长度
 * */
size_t deal_response(char* ptr, size_t size, size_t nmemb, void* userdata){
    FILE* fp = (FILE*)userdata;
    int count = size * nmemb;
    int fwrite_len = 0;
    //这个应该返回已经成功写的数据
    fwrite_len = fwrite(ptr, size, nmemb, fp);
    printf("读取数据的总长度：%d\n", count);
    printf("已经成功写入文件的长度: %d\n", fwrite_len);
    return fwrite_len;

}
int main(int argc, char *argv[]){
    CURL* curl = NULL;
    CURLcode res;
    curl = curl_easy_init();
    if(curl == NULL){
        return -1;
    }

    FILE* fp = NULL;
    fp = fopen("./file.txt", "w");
    if(fp == NULL){
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "http://10.108.37.188:8090/");
    //更改curl为post请求
    curl_easy_setopt(curl, CURLOPT_POST, 1);

    //给post请求提供一些post数据
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTDATA);

    //给curl提供一个回调函数，用来处理服务器的返回数据
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, deal_response);

    //给回调函数传递一个形参
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    //向远程提交请求,一直阻塞，直到服务器响应访问数据
    res = curl_easy_perform(curl);

    if(res != CURLE_OK){
        printf("perform error res = %d\n", res);
        return -1;
    }
    //处理服务器响应数据
    curl_easy_cleanup(curl);
    fclose(fp);
    return 0;
}
