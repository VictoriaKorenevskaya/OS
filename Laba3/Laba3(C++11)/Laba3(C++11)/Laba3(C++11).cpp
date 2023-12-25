#include <mutex>
#include <condition_variable>
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

mutex mut1, mut2;
condition_variable cv;
int K = -1;
bool work_finish = false, count_element_finish = false;

void Work(int& K, int& size, vector<double>& input_array, vector<double>& result)
{
    unique_lock<mutex> ul(mut1);

    cv.wait(ul, [&] {
        return K != -1;
        });

    int count_ = 0;

    for (int i = 0; i < size; i++)
    {
        if (input_array[i] > 0)
        {
            result[count_] = input_array[i];
            count_++;
        }

        if (K == count_)
        {
            break;
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (input_array[i] <= 0)
        {
            result[count_] = input_array[i];
            count_++;
        }

        if (K == count_)
        {
            break;
        }
    }

    work_finish = true;
    ul.unlock();
    cv.notify_all();
    return;
}

void CountElement(vector<double>& result, int& res)
{
    unique_lock<mutex> ul(mut1);

    cv.wait(ul, [&] {
        return work_finish;
        });

    for (int i = 0; i < K; i++)
    {
        int a = result[i];
        if (a == result[i])
        {
            res++;
        }
    }

    count_element_finish = true;
    ul.unlock();
    cv.notify_all();

    return;
}


int main()
{
    int size;

    cout << "Enter array size: ";
    cin >> size;
    vector<double> input_array(size);
    vector<double> result(size);

    double a;
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < size; i++)
    {
        cin >> a;
        input_array[i] = a;
    }
    int res = 0;

    thread t1(Work, ref(K), ref(size), ref(input_array), ref(result));
    thread t2(CountElement, ref(result), ref(res));

    cout << "Enter the value of K: ";
    cin >> K;

    cv.notify_all();

    unique_lock<mutex> ul(mut2);

    cv.wait(ul, [&] {
        return work_finish;
        });

    cout << "First K elements: ";
    for (int i = 0; i < K; i++)
    {
        cout << result[i] << " ";
    }

    cv.wait(ul, [&] {
        return count_element_finish;
        });

    cout << endl;
    cout << "The number of integers in the first K elements array : ";
    cout << res;

    cout << endl;
    cout << "Remaining elements: ";
    for (int i = K; i < size; i++)
    {
        cout << input_array[i] << " ";
    }

    t1.join();
    t2.join();

    return 0;
}
