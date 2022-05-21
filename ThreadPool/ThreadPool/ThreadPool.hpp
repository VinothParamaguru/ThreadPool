//
//  ThreadPool.hpp
//  ThreadPool
//
//  Created by Vinoth Paramaguru on 20/05/2022.
//

#ifndef ThreadPool_hpp
#define ThreadPool_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <unistd.h>
#include <mutex>
#include <condition_variable>

using namespace std;

class CThreadPool {
    
    vector<thread> m_thread_pool;
    queue<function<int()>> m_job_queue;
    mutex m_queue_mutex;
    condition_variable m_queue_cv;
    bool m_thread_running;
    
    int m_nthreads;
    
public:
    CThreadPool(int n_threads);
    ~CThreadPool();
    
    void Run();
    void AddJob(function<int()> job);
    void Exit();
    
};

#endif /* ThreadPool_hpp */
