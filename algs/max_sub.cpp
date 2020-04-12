#include<vector>
#include<iostream>

// brute-force solution  complexity O(n^2)

// return a three size vector record max-sub {begin, end, value}
std::vector<int> brute(const std::vector<int> &input){
    // initialize the result 
    int beg = 0, max = input.front(), size = input.size();
    std::vector<int> result({beg, beg+1, max});
    for(int beg = 0; beg < size; ++beg){
        int max_temp = 0;
        for(int end = beg ; end < size; ++end){
            max_temp += input[end];
            if(max_temp > max){
                result[0] = beg;
                result[1] = end + 1;
                result[2] = max_temp;
                max = max_temp;
            }
        }
    }
    return result;
}

// divide-and-conquer solution  complexity O(nlogn)

std::vector<int> front_find(const std::vector<int> &total, int mid){
    int beg = mid, end = mid + 1, max = total[mid], maxtemp = 0;
    std::vector<int> result({beg,end,max});
    for(; beg >= 0; --beg){
        maxtemp += total[beg];
        if(maxtemp > max){
            result[0] = beg;
            max = maxtemp;
            result[2] = max;
        }
    }
    return result;
}

std::vector<int> end_find(const std::vector<int> &total, int mid){
    int beg = mid + 1, end = mid + 1, max = total[mid], maxtemp = 0;
    std::vector<int> result({beg,end,max});
    for(; end < total.size(); ++end){
        maxtemp += total[end];
        if(maxtemp > max){
            result[1] = end + 1;
            max = maxtemp;
            result[2] = max;
        }
    }
    return result;
}

std::vector<int> merge_result(const std::vector<int> &lft, const std::vector<int> &rht ){
    return {lft[0],rht[1],lft[2]+rht[2]};
}

std::vector<int> divide(const std::vector<int>& input){
    if (input.size() == 1){
        return {0,1,input.front()};
    }
    else{
        std::vector<int> lft(input.begin(),input.begin() + input.size()/2);
        std::vector<int> rht(input.begin() + input.size()/2 ,input.end());
        auto lft_result = divide(lft);
        auto rht_result = divide(rht);
        auto mid_result = merge_result(front_find(input,input.size()/2 - 1),end_find(input,input.size()/2 - 1));
        if((mid_result[2] >= lft_result[2]) && (mid_result[2] >= rht_result[2])){
            return mid_result;
        }
        else if ((lft_result[2] >= mid_result[2]) && (lft_result[2] >= rht_result[2]))
        {
           return lft_result;
        }
        else{
            rht_result[0] += lft.size();
            rht_result[1] += lft.size();
            return rht_result;
        }
    }
}

// linear solution
std::vector<int> linear(const std::vector<int> &input){
// initialize result
    std::vector<int> result({0,1,input.front()});
    int max = input.front(), max_temp = 0,max_beg = 0, max_end = 1, beg_temp = 0;
    for(auto beg = 0; beg < input.size(); ++beg){
        if(max_temp < 0){
            max_temp = 0;
            beg_temp = beg;
        }
        max_temp += input[beg];
        if(max_temp > max){
            max = max_temp;
            max_beg = beg_temp;
            max_end = beg + 1;
        }
    }
    return {max_beg,max_end,max};
}

int main(){
    std::vector<int> input = {1,2,3,4,-1};
    auto result = linear(input);
    for(auto &c:result){
        std::cout<<c<<" ";
    }
    return 0;
}