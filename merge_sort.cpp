#include<iostream>
#include<vector>

// insertion sort
void sort_my(std::vector<int> &data){
    for(std::vector<int>::size_type i = 1; i < data.size(); ++i){
        auto j = i;
        auto key = data[i];
        for(int k = i - 1; k >= 0; --k,--j){
            if(key > data[k]){
                data[j] = data[k];
            }
            else
                break;
        }
        data[j] = key;
    }
}

//merge sort
// merge two sorted vector
std::vector<int> merge(std::vector<int> lft, std::vector<int> rht){
    auto lbeg = lft.begin(), lend = lft.end(), rbeg = rht.begin(), rend = rht.end();
    std::vector<int> result;
    while (lbeg != lend || rbeg !=rend)
    {
         if(lbeg != lend && rbeg != rend && *lbeg <= *rbeg){
        result.push_back(*lbeg);
        ++lbeg;
    }
    else if (lbeg != lend && rbeg != rend)
    {
        result.push_back(*rbeg);
        ++rbeg;
    }
    else if (lbeg == lend)
    {   
        result.insert(result.end(),rbeg,rend);
        rbeg = rend;
    }
    else
    {
        result.insert(result.end(),lbeg,lend);
        lbeg = lend;
    }
    }
    return result;
}

// merge sort recursion
std::vector<int> merge_sort(std::vector<int> &data){
    if(data.size() == 1){
        return data;
    }
    else{
        std::vector<int> lft(data.begin(),data.begin() + data.size()/2); 
        std::vector<int> rht(data.begin() + data.size()/2,data.end()); 
        return merge(merge_sort(lft),merge_sort(rht));
    }
}



int main(){
    std::vector<int> data1 = {1,3,2,4,5,1},data2 = {1,2,4};
    auto data3 = merge_sort(data1);
    for(auto &c:data3){
        std::cout<<c<<" ";
    }
    return 0;
}