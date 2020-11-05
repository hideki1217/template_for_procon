#include<bits/stdc++.h>

using namespace std;

class Matrix{
private:
    int _col,_row;
    vector<vector<double>> _matrix;
public:
    Matrix(int col,int row):_col(col),_row(row){
        _matrix.resize(col,vector<double>(row,0));
    }
    Matrix(const Matrix &obj){
        _col=obj._col;
        _row=obj._row;
        for(int i=0;i<_col;i++){
            for(int j=0;j<_row;j++){
                _matrix[i][j]=obj._matrix[i][j];
            }
        }
    }
    double &operator()(int col,int row){
        return _matrix[col][row];
    } 
    Matrix &operator=(const Matrix &A) {
        if(_col==A._col&&_row==A._row){
            for(int i=0;i<_col;i++){
                for(int j=0;j<_row;j++){
                    _matrix[i][j]=A._matrix[i][j];
                }
            }
            return *this;
        }else throw new InvalidMatrixException("Invalid size matrix");
    }
    Matrix &operator*=(long long a ){
        for(int i=0;i<_col;i++){
            for(int j=0;j<_row;j++){
                _matrix[i][j]=a*_matrix[i][j];
            }
        }
        return *this;
    }
    Matrix operator-() const {return Matrix(*this)*=-1;}
    Matrix &operator+=(const Matrix &A){
        if( A._col==_col&&A._row==_row){
            for(int i=0;i<_col;i++){
                for(int j=0;j<_row;j++){
                    _matrix[i][j]=A._matrix[i][j]+_matrix[i][j];
                }
            }
            return *this;
        }
        throw new InvalidMatrixException("invalid size matrix");
    }
    Matrix operator-=(const Matrix &A){
        if( A._col==_col&&A._row==_row){
            for(int i=0;i<_col;i++){
                for(int j=0;j<_row;j++){
                    _matrix[i][j]=_matrix[i][j]-A._matrix[i][j];
                }
            }
            return *this;
        }
        throw new InvalidMatrixException("invalid size matrix");
    }
    Matrix operator*(const Matrix A)const{
        if(_row==A._col){
            Matrix R(_col,A._row);
            for(int i=0;i<_col;i++){
                for(int j=0;j<A._row;j++){
                    for(int l=0;l<_row;l++){
                        R._matrix[i][j]+=_matrix[i][l]*A._matrix[l][j];
                    }
                }
            }
            return R;
        }else throw new InvalidMatrixException("invalid size matrix");
    }
    Matrix operator-(const Matrix A)const{return Matrix(*this)-=A ;}
    Matrix operator+(const Matrix A)const{return Matrix(*this)+=A ;}

    bool operator!=(const Matrix A)const{
        if(_col!=A._col||_row!=A._row)return 1;
        for(int i=0;i<_col;i++){
            for(int j=0;j<_row;j++){
                if(_matrix[i][j]!=A._matrix[i][j])return 1;
            }
        }
        return 0;
    }
    bool operator==(const Matrix A)const{
        if(_col!=A._col||_row!=A._row)return 0;
        for(int i=0;i<_col;i++){
            for(int j=0;j<_row;j++){
                if(_matrix[i][j]!=A._matrix[i][j])return 0;
            }
        }
        return 1;
    }
    
    void setElement(pair<int,int> pos,long long x){
        int col=pos.first,row=pos.second;
        if(1<=col && col<=_col && 1<=row && row<=_row){
            _matrix[col][row]=x;
        }else throw new InvalidMatrixException("invalid size matrix");
    }
    void setElement(int col,int row,long long x){ setElement({col,row},x); }
    void setElements(const vector<vector<double>> &elements){
        int col=elements.size(),row=elements[0].size();
        if(col==_col&&row==_row){
            for(int i=0;i<col;i++){
                for(int j=0;j<row;j++){
                    this->_matrix[i][j]=elements[i][j];
                }
            }
        }else throw new InvalidMatrixException("invalid size matrix");
    }
    
    int getColumn(){return _col;}
    int getRow(){return _row;}
    
    class InvalidMatrixException : public runtime_error{
    public:     //元々std::runtime_errorにある文字列↓   
        InvalidMatrixException(const char *_Message)
            : runtime_error(_Message){}
            //↓追加のエラー情報を返すGetter
        int returncode(){
            return _Errinfo;
        }
    private:
        int _Errinfo;
        
    };
};