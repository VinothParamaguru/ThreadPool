//
//  ThreadPool.cpp
//  ThreadPool
//
//  Created by Vinoth Paramaguru on 20/05/2022.
//

#include "ThreadPool.hpp"


CThreadPool::CThreadPool(int n_threads) :
    m_thread_pool(),
    m_job_queue(),
    m_queue_mutex(),
    m_queue_cv(),
    m_thread_running(true),
    m_nthreads(n_threads) {
    
    // check the no if threads asked by the client is less than the hardware
    // concurrency supported in the machine
    
    int max_threads_supported = std::thread::hardware_concurrency();
    if(m_nthreads > max_threads_supported) {
        m_nthreads = max_threads_supported;
    }
    
    // create the thread objects
    for (int i = 1; i <= m_nthreads; ++i) {
        m_thread_pool.push_back(thread(&CThreadPool::Run, this));
    }
}

void CThreadPool::Run() {
    
    function<int()> job;
    
    {
        unique_lock<mutex> lock(m_queue_mutex);
        m_queue_cv.wait(lock, [this](){
            return not m_job_queue.empty() or not m_thread_running;
        });
        // store the job for the thread to execute
        job = m_job_queue.front();
        m_job_queue.pop();

    }
    
    // execute the job
    auto result = job();
    
    cout << "\n The Result of the operation is = " << result;
    
}

void CThreadPool::AddJob(function<int()> job) {
    
    {
        unique_lock<mutex> lock(m_queue_mutex);
        m_job_queue.push(job);
        m_queue_cv.notify_one();
    }
    
}

void CThreadPool::Exit() {
    {
        unique_lock<mutex> lock(m_queue_mutex);
        m_thread_running = true;
        m_queue_cv.notify_all();
    }
}

CThreadPool::~CThreadPool() {
    // join all the threads
    for(int i = 0; i < m_thread_pool.size(); ++i) {
        if(m_thread_pool[i].joinable()) {
            m_thread_pool[i].join();
        }
    }
}


