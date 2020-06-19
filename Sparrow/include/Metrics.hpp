#ifndef METRICS_HPP
#define METRICS_HPP
#include <chrono>
#include <string>
#include <ostream>
#include <list>
#include <unordered_map>
#include <algorithm>
struct Metric
{
    std::string name;
    size_t count;
    std::chrono::nanoseconds sum;
    std::chrono::nanoseconds max;
};

struct ScopedMetric
{
    explicit ScopedMetric(Metric *metric);
    ~ScopedMetric();

private:
    Metric *metric;
    std::chrono::high_resolution_clock::time_point start;
};

struct Metrics
{
    static Metrics *GetInstance();
    ~Metrics();

    Metric *NewMetric(const std::string &name);
    void Report(std::ostream &out);
    void Reset();
    Metric *GetMetric(const std::string &name);

private:
    std::list<Metric *> metrics;
    std::unordered_map<std::string, Metric *> map;
};

#define METRIC_RECORD(name)                                                         \
    static Metric *metrics_h_metric =                                               \
        Metrics::GetInstance() ? Metrics::GetInstance()->NewMetric(name) : nullptr; \
    ScopedMetric metrics_h_scoped(metrics_h_metric);

inline ScopedMetric::ScopedMetric(Metric *metric_)
{
    metric = metric_;
    if (!metric)
        return;
    start = std::chrono::high_resolution_clock::now();
}

inline ScopedMetric::~ScopedMetric()
{
    if (!metric)
        return;
    metric->count++;
    auto dt = std::chrono::high_resolution_clock::now() - start;
    metric->sum += dt;
    if (dt > metric->max)
        metric->max = dt;
}

inline Metric *Metrics::NewMetric(const std::string &name)
{
    Metric *metric = new Metric;
    metric->name = name;
    metric->count = 0;
    metric->sum = std::chrono::nanoseconds::zero();
    metric->max = std::chrono::nanoseconds::zero();
    metrics.emplace_back(metric);
    return metric;
}

Metrics *Metrics::GetInstance()
{
    static Metrics s_metrics;
    return &s_metrics;
}

Metrics::~Metrics()
{
    for (auto it = metrics.begin(); it != metrics.end(); it++)
    {
        delete *it;
    }
}

void Metrics::Report(std::ostream &out)
{
    int width = 0;

    std::vector<Metric *> temp_metrics;
    metrics.resize(metrics.size());

    for (auto it = metrics.begin(); it != metrics.end(); it++)
    {
        temp_metrics.emplace_back(*it);
    }

    std::sort(temp_metrics.begin(), temp_metrics.end(), [](const Metric *a, const Metric *b) {
        return a->sum > b->sum;
    });

    for (auto it = temp_metrics.begin(); it != temp_metrics.end(); it++)
        width = std::max((int)(*it)->name.size(), width);

    size_t buf_size = 120;
    char *buf = new char[buf_size];
    snprintf(buf, buf_size, "%-*s\t%-6s\t%-9s\t%-9s\t%s", width, "metrics", "count", "avg (ms)", "max (ms)", "total (ms)");
    out << buf << std::endl;

    size_t n = 0;
    for (auto it = temp_metrics.begin(); it != temp_metrics.end(); it++)
    {
        Metric *metric = *it;
        double total = std::chrono::duration_cast<std::chrono::microseconds>(metric->sum).count();
        double avg = std::chrono::duration_cast<std::chrono::microseconds>(metric->sum).count() / metric->count;
        double max = std::chrono::duration_cast<std::chrono::microseconds>(metric->max).count();
        snprintf(buf, buf_size, "%-*s\t%-6d\t%-8.1f\t%-8.1f\t%.1f", width, metric->name.c_str(), metric->count, avg, max, total);
        out << buf << std::endl;
    }
    delete[] buf;
}

void Metrics::Reset()
{
    for (auto it = metrics.begin(); it != metrics.end(); it++)
    {
        Metric *metric = *it;
        metric->count = 0;
        metric->sum = std::chrono::nanoseconds::zero();
        metric->max = std::chrono::nanoseconds::zero();
    }
}

Metric *Metrics::GetMetric(const std::string &name)
{
    if (map.find(name) != map.end())
    {
        Metric *metric= map[name];   
        return metric;
    }
    else
    {
        Metric *metric = NewMetric(name);
        auto metrics_it = metrics.back();
        map[name] = metrics_it;
        return metric;
    }
}
#endif