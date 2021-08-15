// Test.cpp : Defines the entry point for the application.
//
#include <Windows.h>
#include <thread>
#include <string>
#include <vector>
#include <Urlmon.h> //for URLDownloadToFile
#pragma comment(lib, "urlmon.lib")
#include <iostream>
#include <mutex>
//以下三个头文件是为了兼容Linux版本（C语言实现）
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#define NUMT 4

//******************Windows版本******************
void win_downLoad(std::string& downloadURL, int num)
{
    std::string savepath = "C:\\tmp\\test" + std::to_string(num) + std::string(".jpg");
    URLDownloadToFile(NULL, downloadURL.c_str(), savepath.c_str(), 0, NULL);
}

//******************Linux版本******************

/**
//NUMT为全局常量4
const char* const urls[NUMT] = {
      //Linux环境下测试文本的下载，以下是下载URL
      "https://curl.se/",

      "ftp://cool.haxx.se/",

      "https://www.cag.se/",

      "www.haxx.se"

};

static void* pull_one_url(void* url)
{
    CURL* curl;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_perform(curl); // ignores error
    curl_easy_cleanup(curl);
    return NULL;
}

int main(int argc, char** argv)
{
    pthread_t tid[NUMT];
    int i;
    // Must initialize libcurl before any threads are started 

    curl_global_init(CURL_GLOBAL_ALL);

    for (i = 0; i < NUMT; i++) {
        //int pthread_create(pthread_t *new_thread_ID,const pthread_attr_t* attr, void* (*start_func)(void*), void* arg);
        int error = pthread_create(&tid[i],

            NULL, // 使用默认属性

            pull_one_url,

            (void*)urls[i]);

        if (0 != error)
            fprintf(stderr, "无法运行线程%d, errno %d\n", i, error);
        else
            fprintf(stderr, "线程 %d, gets %s\n", i, urls[i]);
    }

    // 等待所有下载进程终止，并通知主进程。
    for (i = 0; i < NUMT; i++) {
        pthread_join(tid[i], NULL);
        fprintf(stderr, "线程 %d 已终止\n", i);
    }
    curl_global_cleanup();
    return 0;
}

**/

int main()
{
    //windows环境下测试图片的下载，以下是图片下载URL
    std::vector<std::string> urlVector{ "https://unsplash.com/photos/aoiUPcoLbBk/download?force=true", "https://unsplash.com/photos/0qGnW6iakaE/download?force=true",
    "https://unsplash.com/photos/fWDe78O7-Ks/download?force=true", "https://www.pexels.com/photo/4652060/download/?search_query=&tracking_id=b3xnayxjgnc" };
    
    std::mutex valMutex0;
    std::mutex valMutex1;
    int image_num = 0;
    const int num_threads = 4;
    std::thread threads[num_threads];
    std::cout << "开始四个线程的下载工作：\n";
    for (size_t i = 0; i < num_threads; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        //加锁防止多个线程同时访问、修改数据
        valMutex0.lock();
        std::string target_url = urlVector.back();
        urlVector.pop_back();
        valMutex0.unlock();

        threads[i] = std::thread(win_downLoad, target_url, image_num);

        valMutex1.lock();
        image_num += 1;
        valMutex1.unlock();
        if (threads[i].joinable())
        {
            threads[i].join();
        }
    }
    /*for (size_t i = 0; i < num_threads; i++)
    {
        if (threads[i].joinable())
        {
            threads[i].join();
        }
    }*/
    std::cout << num_threads << "个下载线程已经完成工作.\n";
    return 0;
}