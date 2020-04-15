#include<vector>
#include<iostream>
#include<array>
#include<memory>
#include<string>
#include<fstream>
#include<ctime>

class Matrix{
    private:
    int row = 0;
    int col = 0;
    double **ptr = nullptr;
    public:
    Matrix() = default;
    Matrix( int input_row, int input_col);
    Matrix( const Matrix & m1);
    ~Matrix();
    void show(); // show the matrix
    void set(double num);  // set matrix number all to num
    friend Matrix operator+ (const Matrix & m1, const Matrix & m2); 
    friend Matrix operator- (const Matrix & m1, const Matrix & m2);
    Matrix& operator= ( const Matrix & m2);
    friend Matrix operator* (Matrix & m1, Matrix & m2);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m1);
    friend std::istream& operator>>(std::istream& is, Matrix& m1);
    friend Matrix transpose(Matrix& m1);
    friend Matrix merge(const Matrix &m1, const Matrix &m2, const Matrix &m3, const Matrix &m4);
    friend Matrix strassen(Matrix &m1, Matrix &m2);
    Matrix lt() const;
    Matrix rt() const;
    Matrix lb() const;
    Matrix rb() const;
};

Matrix::Matrix( int input_row, int input_col):row(input_row), col(input_col){
    if((input_row != 0) && (input_col != 0)){
        ptr = new double*[row];
        for(int i = 0; i < row; ++i){
            ptr[i] = new double[col];
        }
    }
    else{
        ptr = nullptr;
    }
}

Matrix::~Matrix(){
    if (ptr != nullptr){
        for(int i = 0; i < row; ++i){
            delete[] ptr[i];
        }
        delete[] ptr;
    }
}

void Matrix::show(){
    if(ptr == nullptr){
        std::cout<< "void matrix!";
    }
    else{
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j)
            std::cout<<ptr[i][j] <<" ";
            std::cout<< '\n';
        }
    }
}

void Matrix::set(double num){
    if(ptr == nullptr){
        std::cout<< "void matrix!";
    }
    else{
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j)
            ptr[i][j] = num;
        }
    }
}

Matrix::Matrix( const Matrix & m1):row(m1.row), col(m1.col){
    if((m1.row!= 0) && (m1.col != 0)){
        ptr = new double*[row];
        for(int i = 0; i < row; ++i){
            ptr[i] = new double[col];
            for(int j = 0; j< col; ++j){
                ptr[i][j] = m1.ptr[i][j];
            }
        }
    }
    else{
        ptr = nullptr;
    }
}

Matrix operator+ (const Matrix & m1, const Matrix & m2){
    if((m1.row == m2.row) && (m1.col == m2.col)){
        Matrix m3(m1);
        for(int i = 0; i < m3.row; ++i){
            for(int j = 0; j< m3.col; ++j){
                m3.ptr[i][j] += m2.ptr[i][j];
            }
        }
        return m3;
    }
    else{
        Matrix nm;
        std::string msg = "this two matrix is not the same dims\n";
        std::cout<<msg;
        return nm;
    }

}

Matrix operator- (const Matrix & m1, const Matrix & m2){
    if((m1.row == m2.row) && (m1.col == m2.col)){
        Matrix m3(m1);
        for(int i = 0; i < m3.row; ++i){
            for(int j = 0; j< m3.col; ++j){
                m3.ptr[i][j] -= m2.ptr[i][j];
            }
        }
        return m3;
    }
    else{
        Matrix nm;
        std::string msg = "this two matrix is not the same dims\n";
        std::cout<<msg;
        return nm;
    }

}

Matrix& Matrix::operator= ( const Matrix & m2){
    if(ptr != nullptr){
        for(int i = 0; i < row; ++i){
            delete[] ptr[i];
        }
        delete[] ptr;
    }
    row = m2.row;
    col = m2.col;
    if( (row != 0) && (col != 0)){
        ptr = new double*[row];
        for(int i = 0; i < row; ++i){
            ptr[i] = new double[col];
            for(int j = 0; j< col; ++j){
                ptr[i][j] = m2.ptr[i][j];
            }
        }
    }
    else{
        ptr = nullptr;
    }
    return *this;
}

Matrix operator*(Matrix & m1, Matrix & m2){
    if( m1.col != m2.row ){
        std::string meg = "can't multiply\n";
        std::cout<<meg;
        return Matrix();
    }
    else{
        Matrix m3(m1.row,m2.col);
            for(int i = 0; i < m3.row; ++ i){
                for(int j = 0; j <m3.col; ++j){
                    for(int k = 0; k < m1.col; ++k){
                        m3.ptr[i][j] += m1.ptr[i][k]*m2.ptr[k][j];
                    }
                }
            }
        return m3;
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& m1){
    if(m1.ptr == nullptr){
        os<< "void matrix!\n";
        return os;
    }
    else{
        for(int i = 0; i < m1.row; ++i){
            os<<'|';
            for(int j = 0; j < m1.col; ++j){
            os<<m1.ptr[i][j] <<" ";
            }
            os<<'|' <<'\n';
        }
        return os;
    }
}

std::istream& operator>>(std::istream& is, Matrix& m1){
    for(int i = 0; i < m1.row; ++i){
        for(int j = 0; j< m1.col; ++j){
            is >> m1.ptr[i][j];
        }
    }
    return is;
}

Matrix transpose(Matrix& m1){
    Matrix m2(m1.col,m1.row);
    for(int i = 0; i< m2.row; ++i){
        for(int j = 0; j<m2.col; ++j){
            m2.ptr[i][j] = m1.ptr[j][i];
        }
    }
    return m2;
}


// Strassen’s algorithm (only for 2^n square matrix)
Matrix Matrix::lt() const{
    Matrix m2(this->row/2,this->col/2);
    for(int i = 0; i < m2.row;++i){
        for(int j = 0; j < m2.col; ++j){
            m2.ptr[i][j] = this->ptr[i][j];
        }
    }
    return m2;
}

Matrix Matrix::rt() const{
    Matrix m2(this->row/2,this->col/2);
    for(int i = 0; i < m2.row;++i){
        for(int j = 0; j < m2.col; ++j){
            m2.ptr[i][j] = this->ptr[i][this->row/2 + j];
        }
    }
    return m2;
}

Matrix Matrix::rb() const{
    Matrix m2(this->row/2,this->col/2);
    for(int i = 0; i < m2.row;++i){
        for(int j = 0; j < m2.col; ++j){
            m2.ptr[i][j] = this->ptr[this->row/2+i][this->row/2 + j];
        }
    }
    return m2;
}

Matrix Matrix::lb() const{
    Matrix m2(this->row/2,this->col/2);
    for(int i = 0; i < m2.row;++i){
        for(int j = 0; j < m2.col; ++j){
            m2.ptr[i][j] = this->ptr[this->row/2+i][j];
        }
    }
    return m2;
}

Matrix merge(const Matrix &m1, const Matrix &m2, const Matrix &m3, const Matrix &m4){
    Matrix m5(m1.row*2,m1.row*2);
    for(int i = 0; i < m1.row;++i){
        for(int j = 0; j < m1.col; ++j){
            m5.ptr[i][j] = m1.ptr[i][j];
            m5.ptr[i][j+m1.row] = m2.ptr[i][j];
            m5.ptr[i+m1.row][j] = m3.ptr[i][j];
            m5.ptr[i+m1.row][j+m1.row] = m4.ptr[i][j];
        }
    }
    return m5;
}

Matrix strassen(Matrix &m1, Matrix &m2){
    if((m1.row == 2 && m2.row == 2)){
        return m1*m2;
    }
    else{
        auto a11 = m1.lt(), a12 = m1.rt(), a21 = m1.lb(), a22 = m1.rb() ,
             b11 = m2.lt(), b12 = m2.rt(), b21 = m2.lb(), b22 = m2.rb();
        auto s1 = b12 - b22,
             s2 = a11 + a12,
             s3 = a21 + a22,
             s4 = b21 - b11,
             s5 = a11 + a22,
             s6 = b11 + b22,
             s7 = a12 - a22,
             s8 = b21 + b22,
             s9 = a11 - a21,
             s10 = b11 + b12;
        auto p1 = strassen(a11,s1),
             p2 = strassen(s2,b22),
             p3 = strassen(s3,b11),
             p4 = strassen(a22,s4),
             p5 = strassen(s5,s6),
             p6 = strassen(s7,s8),
             p7 = strassen(s9,s10);
        auto c11 = p5 + p4 - p2 + p6,
             c12 = p1 + p2,
             c21 = p3 + p4,
             c22 = p5 + p1 - p3 - p7;
        return merge(c11,c12,c21,c22);
    }

}


int main(){
    clock_t startTime,endTime;
    Matrix m1(64,64);
    m1.set(10);
    Matrix m4(64,64);
    m4.set(8);
    startTime = clock();
    auto m2 = m1*m4;
    endTime = clock();
    std::cout<<"\n the run time is :" << (double)(endTime - startTime) / CLOCKS_PER_SEC<<'\n';
    std::cout<<"\n =================\n";
    startTime = clock();
    auto m3 = strassen(m1,m4);
    endTime = clock();
    std::cout<<"\n the run time is :" << (double)(endTime - startTime) /CLOCKS_PER_SEC <<'\n';
    return 0;
}



