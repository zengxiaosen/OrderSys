#include <curl/curl.h>


int main() {


    //1 创建一个curl句柄
    CURL *curl = NULL;
    CURLcode res;
    curl = curl_easy_init();
    if(curl == NULL){
        printf("curl init error...");
        return 1;
    }
    //2 给这个句柄设置一些参数（服务器ip，域名，...，端口...）
    res = curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
    if(res != CURLE_OK){
        printf("curl set opt url error");
        return 1;
    }
    res = curl_easy_setopt(curl, CURLOPT_POST, 0);
    if(res != CURLE_OK){
        printf("curl setopt get error");
        return 1;
    }
    //3 将请求提交（真正发出请求）
    res = curl_easy_perform(curl);
    if(res != CURLE_OK){
        printf("curl perform error");
        return 1;
    }

    //4 处理从服务器返回的数据
    //如果不处理返回数据，curl默认会把服务器的返回数据打印到stdout



    //5 释放curl句柄
    curl_easy_cleanup(curl);

    return 0;
}