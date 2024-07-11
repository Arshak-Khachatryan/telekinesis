#include <../headers/spreadsheet.h>

SpreadSheet::SpreadSheet():rowcnt(2),colcnt(2){
    board = new Cell*[rowcnt];
    for(int i = 0; i<rowcnt; i++){
        board[i] = new Cell[colcnt];
    }
}

SpreadSheet::SpreadSheet(const SpreadSheet &rhv):rowcnt(rhv.rowcnt),colcnt(rhv.colcnt){
    board = new Cell*[rowcnt];
    for(int i = 0; i<rowcnt; i++){
        board[i] = new Cell[colcnt];
    }

    for(int i = 0; i<rowcnt; i++){
        for(int j = 0; j<colcnt; j++){
            board[i][j] = rhv.board[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet &&rhv):rowcnt(rhv.rowcnt),colcnt(rhv.colcnt){
    board = rhv.board;
    rhv.board = nullptr;
    rhv.rowcnt = 0;
    rhv.colcnt = 0;
}

SpreadSheet::SpreadSheet(size_t size):rowcnt(size),colcnt(size){
    board = new Cell*[rowcnt];
    for(int i = 0; i<rowcnt; i++){
        board[i] = new Cell[colcnt];
    }
}

SpreadSheet::SpreadSheet(size_t row, size_t col):rowcnt(row),colcnt(col){
    board = new Cell*[row];
    for(int i = 0; i<row; i++){
        board[i] = new Cell[col];
    }
}

SpreadSheet::~SpreadSheet(){
    for(int i = 0; i<rowcnt; i++){
        delete[] board[i];
    }
    delete[] board;
}

const SpreadSheet& SpreadSheet::operator=(const SpreadSheet &rhv){
    if(&rhv == this){
        return *this;
    }

    for(int i = 0; i<rowcnt; i++){
        delete[] board[i];
    }
    delete[] board;

    rowcnt = rhv.rowcnt;
    colcnt = rhv.colcnt;
    board = new Cell*[rowcnt];
    for(int i = 0; i<rowcnt; i++){
        board[i] = new Cell[colcnt];
    }

    for(int i = 0; i<rowcnt; i++){
        for(int j = 0; j<colcnt; j++){
            board[i][j] = rhv.board[i][j];
        }
    }

    return *this;
}

const SpreadSheet &SpreadSheet::operator=(SpreadSheet &&rhv){
    for(int i = 0; i<rowcnt; i++){
        delete[] board[i];
    }
    delete[] board;

    board = rhv.board;
    rowcnt = rhv.rowcnt;
    colcnt = rhv.colcnt;
    rhv.board = nullptr;
    rhv.rowcnt = 0;
    rhv.colcnt = 0;

    return *this;
}

SpreadSheet::Column SpreadSheet::operator[](size_t pos){
    if(pos >= rowcnt){
        throw std::out_of_range("Column index out of range");
    }
    return SpreadSheet::Column(board[pos]);
}

const SpreadSheet::Column SpreadSheet::operator[](size_t pos) const{
    if(pos >= rowcnt){
        throw std::out_of_range("Column index out of range");
    }
    return SpreadSheet::Column(board[pos]);
}

void SpreadSheet::clear() noexcept{
    if(board){
        for(int i = 0; i<rowcnt; i++){
            delete[] board[i];
        }
        delete[] board;

        board = nullptr;
        rowcnt = 0;
        colcnt = 0;
    }
}

size_t SpreadSheet::row() const{
    return rowcnt;
}

size_t SpreadSheet::col() const{
    return colcnt;
}

void SpreadSheet::mirrorH(){
    if(!board){
        throw std::logic_error("No elements in board");
    }

    if(rowcnt == 1){
        return;
    }

    for(int i = 0; i<rowcnt/2; i++){
        for(int j = 0; j<colcnt; j++){
            std::swap(board[i][j],board[rowcnt-i-1][j]);
        }
    }
}

void SpreadSheet::mirrorV(){
    if(!board){
        throw std::logic_error("No elements in board");
    }

    if(colcnt == 1){
        return;
    }

    for(int i = 0; i<rowcnt; i++){
        for(int j = 0; j<colcnt/2; j++){
            std::swap(board[i][j],board[i][colcnt-j-1]);
        }
    }
}

void SpreadSheet::mirrorD(){
    if(!board){
        throw std::logic_error("No elements in board");
    }

    if(rowcnt == 1 || colcnt == 1){
        return;
    }

    if(rowcnt == colcnt){
        for(int i = 0; i<rowcnt; i++){
            for(int j = i+1; j<colcnt; j++){
                std::swap(board[i][j],board[j][i]);
            }
        }
    }else{
        Cell** tmpBoard = new Cell*[colcnt];
        for(int i = 0; i<colcnt; i++){
            tmpBoard[i] = new Cell[rowcnt];
        }
        for(int i = 0; i<rowcnt; i++){
            for(int j = 0; j<colcnt; j++){
                tmpBoard[j][i] = board[i][j];
            }
        }

        for(int i = 0; i<rowcnt; i++){
            delete[] board[i];
        }
        delete[] board;

        std::swap(rowcnt,colcnt);

        board = tmpBoard;
    }
}

void SpreadSheet::mirrorSD(){
    if(rowcnt == 0){
        throw std::out_of_range("No elements in SpreadSheet");
    }
    if (rowcnt == 1){return;}
    if (rowcnt == colcnt){
        for(int i = 0; i<rowcnt;i++){
            for(int j = 0; j<rowcnt-i;j++){
                std::swap(board[i][j],board[rowcnt-j-1][colcnt-i-1]);
            }
        }
    }else{
        Cell** newBoard = new Cell*[colcnt];
        for(int i = 0; i<colcnt;i++){
            newBoard[i] = new Cell[rowcnt];
        }
        for(int i = 0; i<colcnt;i++){
            for(int j = 0;j<rowcnt;j++){
                newBoard[i][j] = board[rowcnt-j-1][colcnt-i-1];
            }
        }
        
        for(int i = 0; i<rowcnt;i++){
            delete [] board[i];
        }
        delete [] board;
        board = newBoard;
        newBoard = nullptr;
        std::swap(rowcnt,colcnt);
    }
}

void SpreadSheet::rotate(int cnt){
    if(cnt < 0){
        throw std::invalid_argument("Count should be not negative");
    }
    cnt %= 4;

    for(int i = 0; i<cnt; i++){
        mirrorD();
        mirrorV();
    }
}

void SpreadSheet::removeRow(size_t row){
    if(!board){
        throw std::invalid_argument("Invalid Argument");
    }

    if(rowcnt == 1){
        clear();
    }

    if(row >= rowcnt){
        throw std::out_of_range("Invalid Argument");
    }

    Cell** tmpBoard = new Cell*[rowcnt-1];
    for(int i = 0; i<rowcnt-1; i++){
        tmpBoard[i] = new Cell[colcnt];
    }

    int tmpRow = 0;
    for(int i = 0; i<rowcnt; i++){
        if(i == row){
            continue;
        }
        for(int j = 0; j<colcnt; j++){
            
            tmpBoard[tmpRow][j] = board[i][j];
        }
        tmpRow++;
    }

    
    for(int i = 0; i<rowcnt; i++){
        delete[] board[i];
    }
    delete[] board;

    board = tmpBoard;
    rowcnt--;
}

void SpreadSheet::removeRows(std::initializer_list<size_t> rows){
    std::vector<size_t> v(rows);
    std::sort(v.begin(),v.end());
    std::reverse(v.begin(),v.end());
    auto iter = std::unique(v.begin(),v.end());
    v.resize(std::distance(v.begin(),iter));

    for(auto it = v.begin(); it != v.end(); it++){
        removeRow(*it);
    }
}

void SpreadSheet::removeCol(size_t col){
    if(!board){
        throw std::invalid_argument("Invalid Argument");
    }

    if(colcnt == 1){
        clear();
    }

    if(col >= colcnt){
        throw std::out_of_range("Invalid Argument");
    }

    Cell** tmpBoard = new Cell*[rowcnt];
    for(int i = 0; i<rowcnt; i++){
        tmpBoard[i] = new Cell[colcnt-1];
    }

    for(int i = 0; i<rowcnt; i++){
        int tmpCol = 0;
        for(int j = 0; j<colcnt; j++){
            if(i == col){
                continue;
            }
            tmpBoard[i][tmpCol] = board[i][j];
            tmpCol++;
        }
        
    }

    for(int i = 0; i<rowcnt; i++){
        delete[] board[i];
    }
    delete[] board;

    board = tmpBoard;
    colcnt--;
}

void SpreadSheet::removeCols(std::initializer_list<size_t> cols){
    std::vector<size_t> v(cols);
    std::sort(v.begin(),v.end());
    std::reverse(v.begin(),v.end());
    auto iter = std::unique(v.begin(),v.end());
    v.resize(std::distance(v.begin(),iter));

    for(auto it = v.begin(); it != v.end(); it++){
        removeCol(*it);
    }
}

void SpreadSheet::resizeRow(size_t r){
    if(r == 0){
        clear();
    }

    if(r == rowcnt){
        return;
    }

    Cell** tmpBoard = new Cell*[r];
    for(int i = 0; i<r; i++){
        tmpBoard[i] = new Cell[colcnt];
    }

    size_t minRow = std::min(r,rowcnt);
    for(int i = 0; i<minRow; i++){
        for(int j = 0; j<colcnt; j++){
            tmpBoard[i][j] = board[i][j];
        }
    }

    for(int i = 0; i<rowcnt; i++){
        delete[] board[i];
    }
    delete[] board;

    board = tmpBoard;
    rowcnt = r;
    
}

void SpreadSheet::resizeCol(size_t c){
    if(c == 0){
        clear();
    }

    if(c == colcnt){
        return;
    }

    Cell** tmpBoard = new Cell*[rowcnt];
    for(int i = 0; i<rowcnt; i++){
        tmpBoard[i] = new Cell[c];
    }

    size_t minCol = std::min(c,colcnt);
    for(int i = 0; i<rowcnt; i++){
        for(int j = 0; j<minCol; j++){
            tmpBoard[i][j] = board[i][j];
        }
    }

    for(int i = 0; i<rowcnt; i++){
        delete[] board[i];
    }
    delete[] board;

    board = tmpBoard;
    colcnt = c;
    
}

void SpreadSheet::resize(size_t r, size_t c){
    resizeRow(r);
    resizeCol(c);
}

SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols){
    std::vector<size_t> vecRows(rows);
    auto it = std::unique(vecRows.begin(),vecRows.end());
    vecRows.resize(distance(vecRows.begin(), it));

    std::vector<size_t> vecCols(cols);
    auto iter = std::unique(vecCols.begin(),vecCols.end());
    vecCols.resize(distance(vecCols.begin(), iter));

    size_t newRow = vecRows.size();
    size_t newCol = vecCols.size();

    SpreadSheet tmp(newRow,newCol);
    
    for(int i = 0; i<newRow;i++){
        for(int j = 0; j<newCol;j++){
            tmp[i][j] = board[vecRows[i]][vecCols[j]];
        }
    }

    return tmp;
}

SpreadSheet::Column::Column(Cell *col):col(col){}

Cell &SpreadSheet::Column::operator[](size_t pos){
    return col[pos];
}

const Cell &SpreadSheet::Column::operator[](size_t pos) const{
    return col[pos];
}

bool operator==(const SpreadSheet &lhv, const SpreadSheet &rhv){
    if(lhv.row() != rhv.row() || lhv.col() != rhv.col()){
        return false;
    }

    size_t r = rhv.row();
    size_t c = rhv.col();
    for(int i = 0; i<r; i++){
        for(int j = 0; j<c; j++){
            if(lhv[i][j] != rhv[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const SpreadSheet &lhv, const SpreadSheet &rhv){
    return !(rhv == lhv);
}

std::ostream &operator<<(std::ostream &out, const SpreadSheet &ob){
    int maxLen = ob.max_length();
    int width = maxLen;//std::min(12, maxLen);
    size_t row = ob.row();
    size_t col = ob.col();

    int totalRowWidth = col * (width + 3) + 1;
    out << std::string(totalRowWidth, '-') << "\n";

    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            if (j < ob.col()) {
                out << "| " << std::setw(width) << std::left << ob[i][j] << " ";
            } else {
                out << "| " << std::setw(width) << std::left << "_ " ;
            }
        }
        out << "|\n" << std::string(totalRowWidth, '-') << "\n";
    }

    return out;

    
}

int SpreadSheet::max_length() const
{ 
    int max = 0;
    for(size_t i = 0; i < rowcnt; ++i)
    {
        for(size_t j = 0; j < colcnt; ++j)
        {
            std::string str = board[i][j];
            max = max < str.length() ? str.length() : max;
        }
    }
    return max;
}