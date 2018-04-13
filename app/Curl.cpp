#include "Curl.h"
Curl::Curl(string url, bool ignoreCert){
    _curl = curl_easy_init();
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    JNIINFO("curl:%s", url.c_str());

    //是否忽略CA认证
    if(ignoreCert == true){
        JNIINFO("%s","ignore CA");
        curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_essy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, false);
    }
}

Curl::~Curl(){
    curl_easy_cleanup(url);
}

bool Curl::execute(string requestData){

    curl_easy_setopt(_curl, CURLOPT_POST, true);
    curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, requestData.c_str());

    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, Curl::dealResponse);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, this);

    CURLcode code = curl_easy_perform(_curl);
    if(code != CURL_OK){
        JNIINFO("curl easy perform error code = %d", code);
        return false;
    }
    return true;

}

string Curl::responseData(){
    return this->_responseData;
}

ssize_t Curl::dealResponse(char* ptr, size_t m, size_t n, void* arg){
    Curl* This = (Curl*)arg;
    int count = m*n;
    //拷贝ptr中的数据到_responseData

    copy(ptr, ptr+count, back_inserter(this->_responseData));
    return count;
}