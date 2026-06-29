//#include <iostream> 
//#include <Eigen> 
//#include <random> 
//#include <set> 
//#include <fstream>  
//#include <vector>
//#include <cassert>
//
//using namespace Eigen;
//using namespace std;
//
//double g(double x) {
//    return x*(1 - x);
//
//    //return -(x * x * (1 - x));
//}
//
//void printSparseMatrix(const SparseMatrix<double>& matrix) {
//    int rows = matrix.rows();
//    int cols = matrix.cols();
//
//    cout << "SparseMatrix (" << rows << "x" << cols << "):" << endl;
//
//    for (int k = 0; k < matrix.outerSize(); ++k) {
//        for (SparseMatrix<double>::InnerIterator it(matrix, k); it; ++it) {
//            int i = it.row();    // Строка
//            int j = it.col();    // Столбец
//            double value = it.value(); // Значение
//
//            cout << "Element (" << i << ", " << j << ") = " << value << endl;
//        }
//    }
//}
//
////vector<vector<double>> softenMatrix(const vector<vector<double>>& matrix, int factor) {
////    int rows = matrix.size();
////    int cols = matrix[0].size();
////    int newRows = rows * factor;
////    int newCols = cols * factor;
////
////    vector<vector<double>> newMatrix(newRows, vector<double>(newCols, 0));
////
////    for (int i = 0; i < rows; ++i) {
////        for (int j = 0; j < cols; ++j) {
////            double value = matrix[i][j];
////
////            // Копируем значение в фактор^2 ячеек новой матрицы
////            for (int x = 0; x < factor; ++x) {
////                for (int y = 0; y < factor; ++y) {
////                    newMatrix[i * factor + x][j * factor + y] = value;
////                }
////            }
////        }
////    }
////
////    return newMatrix;
////}
//
////vector<vector<double>> softenMatrix(const vector<vector<double>>& matrix, int factor) {
////    int rows = matrix.size();
////    int cols = matrix[0].size();
////    int newRows = rows * factor;
////    int newCols = cols * factor;
////
////    vector<vector<double>> newMatrix(newRows, vector<double>(newCols, 100));
////
////    for (int i = 0; i < rows; ++i) {
////        for (int j = 0; j < cols; ++j) {
////            double value = matrix[i][j];
////
////             // элемент НЕ на границе, записываем его только в центр блока
////            if (i > 0 && i < rows - 1 && j > 0 && j < cols - 1) {
////                int centerX = i * factor + factor / 2;
////                int centerY = j * factor + factor / 2;
////                newMatrix[centerX][centerY] = value;
////            }
////            else { // Иначе записываем его только в крайние точки
////                if (i == 0) {
////                    for (int y = j * factor; y < (j + 1) * factor; ++y) {
////                        newMatrix[0][y] = value;
////                    }
////                }
////                if (i == rows - 1) {
////                    for (int y = j * factor; y < (j + 1) * factor; ++y) {
////                        newMatrix[newRows - 1][y] = value;
////                    }
////                }
////                if (j == 0) {
////                    for (int x = i * factor; x < (i + 1) * factor; ++x) {
////                        newMatrix[x][0] = value;
////                    }
////                }
////                if (j == cols - 1) {
////                    for (int x = i * factor; x < (i + 1) * factor; ++x) {
////                        newMatrix[x][newCols - 1] = value;
////                    }
////                }
////            }
////        }
////    }
////
////    return newMatrix;
////}
//
////vector<vector<double>> softenMatrix(const vector<vector<double>>& matrix, int factor) {
////    assert(factor >= 1);
////    int rows = matrix.size();
////    int cols = matrix[0].size();
////    int newRows = rows * factor;
////    int newCols = cols * factor;
////
////    // Инициализируем «новую» матрицу каким-нибудь значением (100 как в вашем примере)
////    vector<vector<double>> newMatrix(newRows, vector<double>(newCols, 100));
////
////    for (int i = 0; i < rows; ++i) {
////        for (int j = 0; j < cols; ++j) {
////            double value = matrix[i][j];
////            bool isBorder = (i == 0 || i == rows - 1 || j == 0 || j == cols - 1);
////
////            // координаты верхнего левого угла блока
////            int baseX = i * factor;
////            int baseY = j * factor;
////
////            if (!isBorder && factor >= 3) {
////                // Центр блока
////                int centerX = baseX + factor / 2;
////                int centerY = baseY + factor / 2;
////
////                // Записываем в три вертикальных пикселя: центр-1, центр, центр+1
////                for (int dx = -1; dx <= 1; ++dx) {
////                    int x = centerX + dx;
////                    // Проверяем, чтобы не выйти за границы новой матрицы
////                    if (x >= 0 && x < newRows) {
////                        newMatrix[x][centerY] = value;
////                    }
////                }
////            }
////            else {
////                // Граничные пиксели: как и раньше, заливаем соответствующие стороны блока
////                if (i == 0) {
////                    for (int y = baseY; y < baseY + factor; ++y) {
////                        newMatrix[0][y] = value;
////                    }
////                }
////                if (i == rows - 1) {
////                    for (int y = baseY; y < baseY + factor; ++y) {
////                        newMatrix[newRows - 1][y] = value;
////                    }
////                }
////                if (j == 0) {
////                    for (int x = baseX; x < baseX + factor; ++x) {
////                        newMatrix[x][0] = value;
////                    }
////                }
////                if (j == cols - 1) {
////                    for (int x = baseX; x < baseX + factor; ++x) {
////                        newMatrix[x][newCols - 1] = value;
////                    }
////                }
////            }
////        }
////    }
////
////    return newMatrix;
////}
//
//vector<vector<double>> softenMatrix(const vector<vector<double>>& matrix, int factor) {
//    assert(factor >= 1);
//    int rows = matrix.size();
//    int cols = matrix[0].size();
//    int newRows = rows * factor;
//    int newCols = cols * factor;
//
//    // Инициализируем «новую» матрицу значением 100 (как в вашем примере)
//    vector<vector<double>> newMatrix(newRows, vector<double>(newCols, 100.0));
//
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            double value = matrix[i][j];
//            bool isBorder = (i == 0 || i == rows - 1 || j == 0 || j == cols - 1);
//
//            // координаты верхнего левого угла блока
//            int baseX = i * factor;
//            int baseY = j * factor;
//
//            if (!isBorder && factor >= 3) {
//                // Центр блока
//                int centerX = baseX + factor / 2;
//                int centerY = baseY + factor / 2;
//
//                // Записываем в три горизонтальных пикселя: центр-1, центр, центр+1
//                for (int dy = -1; dy <= 1; ++dy) {
//                    int y = centerY + dy;
//                    if (y >= 0 && y < newCols) {
//                        newMatrix[centerX][y] = value;
//                    }
//                }
//            }
//            else {
//                // Граничные пиксели: заливаем края блока, как в вашем оригинале
//                if (i == 0) {
//                    for (int y = baseY; y < baseY + factor; ++y) {
//                        newMatrix[0][y] = value;
//                    }
//                }
//                if (i == rows - 1) {
//                    for (int y = baseY; y < baseY + factor; ++y) {
//                        newMatrix[newRows - 1][y] = value;
//                    }
//                }
//                if (j == 0) {
//                    for (int x = baseX; x < baseX + factor; ++x) {
//                        newMatrix[x][0] = value;
//                    }
//                }
//                if (j == cols - 1) {
//                    for (int x = baseX; x < baseX + factor; ++x) {
//                        newMatrix[x][newCols - 1] = value;
//                    }
//                }
//            }
//        }
//    }
//
//    return newMatrix;
//}
//
//void printMatrix(const vector<vector<double>>& matrix) {
//    int rows = matrix.size();
//    int cols = matrix[0].size();
//
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            double value = static_cast<int>(matrix[i][j] * 100) / 100.0;
//            cout << value << " ";
//        }
//        cout << endl;
//    }
//}
//
//void writeMatrixWithCoordinatesToFile(const std::vector<std::vector<double>>& matrix, double xMin, double xMax, double yMin, double yMax) {
//
//    size_t rows = matrix.size();
//    size_t cols = matrix[0].size();
//
//    std::string filename = "matrixDirOkrLines_" + std::to_string(rows) + "x" + std::to_string(cols) + ".txt";
//
//    std::ofstream file(filename);
//    if (!file.is_open()) {
//        std::cerr << "Ошибка открытия файла!" << std::endl;
//        return;
//    }
//
//    //step delenia
//    double xStep = (xMax - xMin) / (cols - 1);
//    double yStep = (yMax - yMin) / (rows - 1);
//
//
//    for (size_t i = 0; i < rows; ++i) {
//        for (size_t j = 0; j < cols; ++j) {
//            double x = xMin + j * xStep; // x
//            double y = yMin + i * yStep; // y
//            double z = matrix[i][j];    // z
//            file << x << " " << y << " " << z << "\n";
//        }
//    }
//
//    file.close();
//    std::cout << "Matrix file name: " << filename << std::endl;
//}
//
//std::vector<std::pair<int, int>> bresenhamLine(int x1, int y1, int x2, int y2) {
//    std::vector<std::pair<int, int>> points;
//
//    int k1, k2, p, x, y, incX, incY;
//
//
//    int dfx = abs(x2 - x1);
//    int dfy = abs(y2 - y1);
//
//    double smer = 0;
//
//    if (x2 == x1)
//        smer = std::numeric_limits<double>::infinity();
//    else
//        smer = static_cast<double>(y2 - y1) / (x2 - x1);
//
//    incX = (x2 > x1) ? 1 : -1;
//    incY = (y2 > y1) ? 1 : -1;
//
//    k1 = (abs(smer) < 1) ? 2 * dfy : 2 * dfx;
//    k2 = (abs(smer) < 1) ? 2 * (dfy - dfx) : 2 * (dfx - dfy);
//    p = (abs(smer) < 1) ? 2 * dfy - dfx : 2 * dfx - dfy;
//    x = x1;
//    y = y1;
//
//    while (x != x2 || y != y2)
//    {
//        //painter->drawPoint(x, y);  
//        points.emplace_back(x, y);
//        // urcuem stvrt od osej
//        if (abs(smer) < 1)
//        {
//            x += incX;
//
//            if (p < 0)
//                p += k1;
//            else
//            {
//                y += incY;
//                p += k2;
//            }
//        }
//        else
//        {
//            y += incY;
//
//            if (p < 0)
//                p += k1;
//            else
//            {
//                x += incX;
//                p += k2;
//            }
//        }
//    }
//
//
//    return points;
//}
//
//
//int main() {
//
//    double a = 1;
//
//    int n = 30;
//    int rows = n;
//    int cols = n;
//    int total_size = rows * cols;
//
//    vector<vector<double>> matrix(rows, vector<double>(cols));
//    double h = (a - 0.0) / (double)(n - 1);
//
//    int x1 = 5, y1_1 = 5, y1_2 = 20; // Начало прямых
//    int x2 = 25, y2_1 = 5, y2_2 = 20; // Конец прямых
//
//    // Узловые точки первой прямой
//    std::vector<std::pair<int, int>> line1 = bresenhamLine(x1, y1_1, x1, y1_2);
//    // Узловые точки второй прямой
//    std::vector<std::pair<int, int>> line2 = bresenhamLine(x2, y2_1, x2, y2_2);
//
//
//    std::ofstream file("lines.txt");
//    if (!file.is_open()) {
//        std::cerr << "Error opening file for writing!" << std::endl;
//        return 1;
//    }
//
//    file << "(* First Line *)\n";
//    file << "line1 = {";
//    for (size_t i = 0; i < line1.size(); ++i) {
//        file << "{" << line1[i].first << ", " << line1[i].second << "}";
//        if (i != line1.size() - 1) file << ", ";
//    }
//    file << "};\n";
//
//    // Записываем точки второй прямой в файл
//    /*file << "(* Second Line *)\n";
//    file << "line2 = {";
//    for (size_t i = 0; i < line2.size(); ++i) {
//        file << "{" << line2[i].first << ", " << line2[i].second << "}";
//        if (i != line2.size() - 1) file << ", ";
//    }
//    file << "};\n";*/
//
//    // Добавляем команду для построения графика в Wolfram Mathematica
//    file << "\nListPlot[{line1, line2}, PlotStyle -> {Red, Blue}, "
//        << "Joined -> True, AspectRatio -> Automatic, "
//        << "AxesLabel -> {\"x\", \"y\"}, PlotMarkers -> Automatic];\n";
//
//    // Закрываем файл
//    file.close();
//
//
//    //std::vector<std::pair<int, int>> points = bresenhamLine(x1, y1, x2, y2);
//
//
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            if (i == 0) {
//                //matrix[i][j] = g(j * h);
//                matrix[i][j] = 100;
//            }
//            else if (j == 0) {
//                //matrix[i][j] = g(i * h);
//                matrix[i][j] = 100;
//            }
//            else if (i == n - 1) {
//                //matrix[i][j] = g(j * h);
//                matrix[i][j] = 100;
//            }
//            else if (j == n - 1) {
//                //matrix[i][j] = g(i * h);
//                matrix[i][j] = 100;
//
//            }
//            else {
//                matrix[i][j] = 100.0;
//            }
//            //matrix[i][j] = 100.0;
//        }
//    }
//
//    for (const auto& point : line1) {
//        int x = point.first;
//        int y = point.second;
//        if (x >= 0 && x < 30 && y >= 0 && y < n) {
//            matrix[x][y] = 10; // Учитываем, что y — строка, x — столбец
//        }
//    }
//
//    for (const auto& point : line2) {
//        int x = point.first;
//        int y = point.second;
//        if (x >= 0 && x < n && y >= 0 && y < n) {
//            matrix[x][y] = 0;
//        }
//    }
//
//    //Eigen::initParallel();
//    SparseMatrix<double> A(n * n, n * n);
//    SparseMatrix<double> temp(n * n, n * n);
//    VectorXd b(n * n), x(n * n);
//
//    A.reserve(Eigen::VectorXi::Constant(n * n, 5));
//
//    #pragma omp parallel for
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            int idx = i * cols + j;
//            if (matrix[i][j] != 100.0) {
//                A.insert(idx, idx) = 1.0;
//                b(idx) = matrix[i][j];
//            }
//            else {
//                A.insert(idx, idx) = 4.0;
//                if (j + 1 > cols - 1) { //2
//                    if (i - 1 < 0) { //5
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (i + 1 > rows - 1) { //6
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx - cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    A.insert(idx, idx - 1) = -2.0;
//                    A.insert(idx, idx + cols) = -1.0;
//                    A.insert(idx, idx - cols) = -1.0;
//                    b(idx) = 0.0;
//                    continue;
//                }
//                if (i - 1 < 0) { // 1
//                    if (j + 1 > cols - 1) { // 5
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (j - 1 < 0) { //8
//                        A.insert(idx, idx + 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    A.insert(idx, idx - 1) = -1.0;
//                    A.insert(idx, idx + cols) = -2.0;
//                    A.insert(idx, idx + 1) = -1.0;
//                    b(idx) = 0.0;
//                    continue;
//                }
//                if (j - 1 < 0) { //4
//                    if (i - 1 < 0) { //8
//                        A.insert(idx, idx + 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (i + 1 > rows - 1) { //7
//                        A.insert(idx, idx - cols) = -2.0;
//                        A.insert(idx, idx + 1) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    A.insert(idx, idx - cols) = -1.0;
//                    A.insert(idx, idx + cols) = -1.0;
//                    A.insert(idx, idx + 1) = -2.0;
//                    b(idx) = 0.0;
//                    continue;
//                }
//                if (i + 1 > rows - 1) { // 3
//                    if (j - 1 < 0) { // 7
//                        A.insert(idx, idx - cols) = -2.0;
//                        A.insert(idx, idx + 1) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (j + 1 > cols - 1) { //6
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx - cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    A.insert(idx, idx - cols) = -2.0;
//                    A.insert(idx, idx - 1) = -1.0;
//                    A.insert(idx, idx + 1) = -1.0;
//                    b(idx) = 0.0;
//                    continue;
//                }
//                A.insert(idx, idx + 1) = -1.0;//i,j+1
//                A.insert(idx, idx - 1) = -1.0;//i,j-1
//                A.insert(idx, idx + cols) = -1.0;//i+1,j
//                A.insert(idx, idx - cols) = -1.0;//i-1,j
//                b(idx) = 0.0;
//            }
//        }
//    }
//
//    /*for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            if (i == 0) {
//                A.insert(j, j) = 1.0;
//                b(j) = g(j * h);
//            }
//            else if (j == 0) {
//                A.insert(i * n, i * n) = 1.0;
//                b(i * n) = g(i * h);
//            }
//            else if (i == n - 1) {
//                A.insert(i * n + j, i * n + j) = 1.0;
//                b(i * n + j) = g(j * h);
//            }
//            else if (j == n - 1) {
//                A.insert(i * n + j, i * n + j) = 1.0;
//                b(i * n + j) = g(i * h);
//            }
//            else {
//                A.insert(i * n + j, i * n + j) = 4.0;
//                A.insert(i * n + j, i * n + j + 1) = -1.0;
//                A.insert(i * n + j, i * n + j - 1) = -1.0;
//                A.insert(i * n + j, (i + 1) * n + j) = -1.0;
//                A.insert(i * n + j, (i - 1) * n + j) = -1.0;
//                b(i * n + j) = 0.0;
//            }
//        }
//    }*/
//    temp = A;
//    A.makeCompressed();
//    BiCGSTAB<SparseMatrix<double>> solver;
//    solver.compute(A);
//    x = solver.solve(b);
//
//    vector<vector<double>> matrixFinal(rows, vector<double>(cols));
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            matrixFinal[i][j] = x(i * cols + j);
//        }
//    }
//
//    double L2Norm = 0.0;
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            L2Norm += h * h * matrixFinal[i][j]* matrixFinal[i][j];
//        }
//    }
//
//    double tL2 = sqrt(L2Norm);
//    L2Norm = tL2;
//    cout << endl;
//    cout << L2Norm << endl;
//
//    double xMin = 0.0, xMax = 30.0;
//    double yMin = 0.0, yMax = 30.0;
//
//    //ofstream file;
//    file.open("solutionTestDefaultNeum3GorCen.txt", ios::out);
//
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            file << i * h << " " << j * h << " " << x(i * n + j) << endl;
//        }
//    }
//
//    file.close();
//    
//    //printMatrix(matrix);
//
//    double sum = 0.0;
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            sum += matrixFinal[i][j];
//        }
//    }
//    sum /= total_size;
//
//    //cout << sum << endl;
//
//    for (int i = 1; i <= 3; i++) {
//        int f = pow(3, i);
//        //cout << f << endl;
//        matrix = softenMatrix(matrix, 3);
//
//        //printMatrix(matrix);
//
//        rows = matrix.size();
//        cols = matrix[0].size();
//        cout << rows << endl;
//        n = rows;
//        cout << n << endl;
//        total_size = rows * cols;
//
//        cout << rows << " " << cols << " " << total_size << endl;
//
//        //printMatrix(matrix);
//
        //A.resize(total_size, total_size);
        //b.resize(total_size);
        //x.resize(total_size);

        //h = (a - 0.0) / (double)(rows - 1);

        //A.reserve(Eigen::VectorXi::Constant(n * n, 5));
//
//        for (int i = 0; i < rows; ++i) {
//            for (int j = 0; j < cols; ++j) {
//                int idx = i * cols + j;
//                if (matrix[i][j] != 100.0) {
//                    A.insert(idx, idx) = 1.0;
//                    b(idx) = matrix[i][j];
//                }
//                else {
//                    A.insert(idx, idx) = 4.0;
//                    if (j + 1 > cols - 1) { //2
//                        if (i - 1 < 0) { //5
//                            A.insert(idx, idx - 1) = -2.0;
//                            A.insert(idx, idx + cols) = -2.0;
//                            b(idx) = 0.0;
//                            continue;
//                        }
//                        if (i + 1 > rows - 1) { //6
//                            A.insert(idx, idx - 1) = -2.0;
//                            A.insert(idx, idx - cols) = -2.0;
//                            b(idx) = 0.0;
//                            continue;
//                        }
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx + cols) = -1.0;
//                        A.insert(idx, idx - cols) = -1.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (i - 1 < 0) { // 1
//                        if (j + 1 > cols - 1) { // 5
//                            A.insert(idx, idx - 1) = -2.0;
//                            A.insert(idx, idx + cols) = -2.0;
//                            b(idx) = 0.0;
//                            continue;
//                        }
//                        if (j - 1 < 0) { //8
//                            A.insert(idx, idx + 1) = -2.0;
//                            A.insert(idx, idx + cols) = -2.0;
//                            b(idx) = 0.0;
//                            continue;
//                        }
//                        A.insert(idx, idx - 1) = -1.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        A.insert(idx, idx + 1) = -1.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (j - 1 < 0) { //4
//                        if (i - 1 < 0) { //8
//                            A.insert(idx, idx + 1) = -2.0;
//                            A.insert(idx, idx + cols) = -2.0;
//                            b(idx) = 0.0;
//                            continue;
//                        }
//                        if (i + 1 > rows - 1) { //7
//                            A.insert(idx, idx - cols) = -2.0;
//                            A.insert(idx, idx + 1) = -2.0;
//                            b(idx) = 0.0;
//                            continue;
//                        }
//                        A.insert(idx, idx - cols) = -1.0;
//                        A.insert(idx, idx + cols) = -1.0;
//                        A.insert(idx, idx + 1) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (i + 1 > rows - 1) { // 3
//                        if (j - 1 < 0) { // 7
//                            A.insert(idx, idx - cols) = -2.0;
//                            A.insert(idx, idx + 1) = -2.0;
//                            b(idx) = 0.0;
//                            continue;
//                        }
//                        if (j + 1 > cols - 1) { //6
//                            A.insert(idx, idx - 1) = -2.0;
//                            A.insert(idx, idx - cols) = -2.0;
//                            b(idx) = 0.0;
//                            continue;
//                        }
//                        A.insert(idx, idx - cols) = -2.0;
//                        A.insert(idx, idx - 1) = -1.0;
//                        A.insert(idx, idx + 1) = -1.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    A.insert(idx, idx + 1) = -1.0;//i,j+1
//                    A.insert(idx, idx - 1) = -1.0;//i,j-1
//                    A.insert(idx, idx + cols) = -1.0;//i+1,j
//                    A.insert(idx, idx - cols) = -1.0;//i-1,j
//                    b(idx) = 0.0;
//                }
//            }
//        }
//        A.makeCompressed();
//        BiCGSTAB<SparseMatrix<double>> solver;
//        solver.compute(A);
//        x = solver.solve(b);
//
//        std::string filename = "matrixNeum3GorCen_" + std::to_string(rows) + "x" + std::to_string(cols) + ".txt";
//
//        std::ofstream file(filename);
//        if (!file.is_open()) {
//            std::cerr << "Ошибка открытия файла!" << std::endl;
//            return 1;
//        }
//
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < n; ++j) {
//                file << i * h << " " << j * h << " " << x(i * n + j) << endl;
//            }
//        }
//
//        vector<vector<double>> matrixFinal1(rows, vector<double>(cols));
//        for (int i = 0; i < rows; ++i) {
//            for (int j = 0; j < cols; ++j) {
//                matrixFinal1[i][j] = x(i * cols + j);
//            }
//        }
//
//        sum = 0.0;
//        for (int i = 0; i < rows; i++) {
//            for (int j = 0; j < cols; j++) {
//                sum += matrixFinal1[i][j];
//            }
//        }
//
//        sum /= total_size;
//
//        //cout << sum << endl;
//
//        L2Norm = 0.0;
//        for (int i = 0; i < rows; i++) {
//            for (int j = 0; j < cols; j++) {
//                L2Norm += h * h * matrixFinal1[i][j] * matrixFinal1[i][j];
//            }
//        }
//
//        tL2 = sqrt(L2Norm);
//        L2Norm = tL2;
//        cout << endl;
//        cout << L2Norm << endl;
//
//        file.open("L2NormList.txt", ios::out);
//
//        //file << L2Norm << endl;
//
//        file.close();
//
//    }
//
//    return 0;
//}

#include <iostream> 
#include <Eigen> 
#include <random> 
#include <set> 
#include <fstream>  
#include <cmath>
#include <iomanip>
#include "gdal_priv.h"
#include "cpl_conv.h" // CPLMalloc

#include <chrono>
using namespace Eigen;
using namespace std;

double g(double x) {
    return x * (1 - x);

    //return -(x * x * (1 - x));
}

void printSparseMatrix(const SparseMatrix<double>& matrix) {
    int rows = matrix.rows();
    int cols = matrix.cols();

    cout << "SparseMatrix (" << rows << "x" << cols << "):" << endl;

    for (int k = 0; k < matrix.outerSize(); ++k) {
        for (SparseMatrix<double>::InnerIterator it(matrix, k); it; ++it) {
            int i = it.row();    // Строка
            int j = it.col();    // Столбец
            double value = it.value(); // Значение

            cout << "Element (" << i << ", " << j << ") = " << value << endl;
        }
    }
}

//vector<vector<double>> softenMatrix(const vector<vector<double>>& matrix, int factor) {
//    int rows = matrix.size();
//    int cols = matrix[0].size();
//    int newRows = rows * factor;
//    int newCols = cols * factor;
//
//    vector<vector<double>> newMatrix(newRows, vector<double>(newCols, 0));
//
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            double value = matrix[i][j];
//
//            // Копируем значение в фактор^2 ячеек новой матрицы
//            for (int x = 0; x < factor; ++x) {
//                for (int y = 0; y < factor; ++y) {
//                    newMatrix[i * factor + x][j * factor + y] = value;
//                }
//            }
//        }
//    }
//
//    return newMatrix;
//}

vector<vector<double>> softenMatrix(const vector<vector<double>>& matrix, int factor) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    int newRows = rows * factor;
    int newCols = cols * factor;

    vector<vector<double>> newMatrix(newRows, vector<double>(newCols, 100));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double value = matrix[i][j];

            // Если элемент НЕ на границе, записываем его только в центр блока
            if (i > 0 && i < rows - 1 && j > 0 && j < cols - 1) {
                int centerX = i * factor + factor / 2;
                int centerY = j * factor + factor / 2;
                newMatrix[centerX][centerY] = value;
            }
            else { // Иначе записываем его только в крайние точки
                if (i == 0) {
                    for (int y = j * factor; y < (j + 1) * factor; ++y) {
                        newMatrix[0][y] = value;
                    }
                }
                if (i == rows - 1) {
                    for (int y = j * factor; y < (j + 1) * factor; ++y) {
                        newMatrix[newRows - 1][y] = value;
                    }
                }
                if (j == 0) {
                    for (int x = i * factor; x < (i + 1) * factor; ++x) {
                        newMatrix[x][0] = value;
                    }
                }
                if (j == cols - 1) {
                    for (int x = i * factor; x < (i + 1) * factor; ++x) {
                        newMatrix[x][newCols - 1] = value;
                    }
                }
            }
        }
    }

    return newMatrix;
}

void printMatrix(const vector<vector<double>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double value = static_cast<int>(matrix[i][j] * 100) / 100.0;
            cout << value << " ";
        }
        cout << endl;
    }
}

void writeMatrixWithCoordinatesToFile(const std::vector<std::vector<double>>& matrix, double xMin, double xMax, double yMin, double yMax) {

    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    std::string filename = "matrixDirOkrLines_" + std::to_string(rows) + "x" + std::to_string(cols) + ".txt";

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }

    //step delenia
    double xStep = (xMax - xMin) / (cols - 1);
    double yStep = (yMax - yMin) / (rows - 1);


    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            double x = xMin + j * xStep; // x
            double y = yMin + i * yStep; // y
            double z = matrix[i][j];    // z
            file << x << " " << y << " " << z << "\n";
        }
    }

    file.close();
    std::cout << "Matrix file name: " << filename << std::endl;
}

std::vector<std::pair<int, int>> bresenhamLine(int x1, int y1, int x2, int y2) {
    std::vector<std::pair<int, int>> points;

    int k1, k2, p, x, y, incX, incY;


    int dfx = abs(x2 - x1);
    int dfy = abs(y2 - y1);

    double smer = 0;

    if (x2 == x1)
        smer = std::numeric_limits<double>::infinity();
    else
        smer = static_cast<double>(y2 - y1) / (x2 - x1);

    incX = (x2 > x1) ? 1 : -1;
    incY = (y2 > y1) ? 1 : -1;

    k1 = (abs(smer) < 1) ? 2 * dfy : 2 * dfx;
    k2 = (abs(smer) < 1) ? 2 * (dfy - dfx) : 2 * (dfx - dfy);
    p = (abs(smer) < 1) ? 2 * dfy - dfx : 2 * dfx - dfy;
    x = x1;
    y = y1;

    while (x != x2 || y != y2)
    {
        //painter->drawPoint(x, y);  
        points.emplace_back(x, y);
        // urcuem stvrt od osej
        if (abs(smer) < 1)
        {
            x += incX;

            if (p < 0)
                p += k1;
            else
            {
                y += incY;
                p += k2;
            }
        }
        else
        {
            y += incY;

            if (p < 0)
                p += k1;
            else
            {
                x += incX;
                p += k2;
            }
        }
    }


    return points;
}

vector<vector<double>> loadMatrixFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error during a reading" << endl;
        return {};
    }

    int rows, cols;
    // Считываем первую строку с размерами матрицы
    if (!(file >> rows >> cols)) {
        cerr << "Ошибка чтения размеров матрицы!" << endl;
        return {};
    }
    // Пропускаем остаток строки после размеров
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<double>> matrix(rows, vector<double>(cols));

    // Построчное чтение матрицы
    for (int i = 0; i < rows; ++i) {
        string line;
        if (!getline(file, line)) {
            cerr << "Ошибка чтения строки " << i << "!" << endl;
            break;
        }
        istringstream iss(line);
        for (int j = 0; j < cols; ++j) {
            if (!(iss >> matrix[i][j])) {
                cerr << "Ошибка считывания элемента в строке " << i << ", столбце " << j << endl;
                break;
            }
        }
    }

    file.close();
    return matrix;
}

//vector<vector<double>> compareValues(vector<vector<double>>& matrixSolution, vector<vector<double>>& matrixData) {
//
//    int rows = matrixSolution.size();
//    int cols = matrixSolution[0].size();
//
//
//    vector<vector<double>> matrix(rows, vector<double>(cols));
//    double difference;
//
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            difference = fabs(matrixSolution[i][j] - matrixData[i][j]);
//            matrix[i][j] = (difference <= 0.1) ? 1.0 : 0.0;
//        }
//    }
//
//    return matrix;
//}


void saveMatrixToPGM(const vector<vector<double>>& matrix, const string& filename) {
    ofstream file(filename, ios::binary);  // Otvárame súbor v binárnom režime
    if (!file) {
        cerr << "Open error!" << endl;
        return;
    }

    int rows = matrix.size();
    int cols = matrix[0].size();

    // Hľadáme minimálnu a maximálnu hodnotu v matici
    double min_value = matrix[0][0];
    double max_value = matrix[0][0];

    for (const auto& row : matrix) {
        for (double value : row) {
            min_value = min(min_value, value);
            max_value = max(max_value, value);
        }
    }

    // PGM hlavička (P2 znamená ASCII formát)
    file << "P2" << endl;
    file << cols << " " << rows << endl;
    file << "255" << endl;  // Maximálna hodnota pre intenzitu pixelov (255 pre škálu šedej)

    // Zapisujeme hodnoty matice do súboru, pričom ich najprv normalizujeme do rozsahu 0-255
    for (const auto& row : matrix) {
        for (double value : row) {
            // Normalizujeme hodnotu medzi 0 a 255
            int pixel_value = static_cast<int>(((value - min_value) / (max_value - min_value)) * 255);
            if (pixel_value < 0) pixel_value = 0;
            if (pixel_value > 255) pixel_value = 255;
            file << pixel_value;
            file << endl;
        }

    }

    file.close();
}

void saveMatrixToFile(const vector<vector<double>>& matrix, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    int rows = matrix.size();
    int cols = (rows > 0) ? matrix[0].size() : 0;

    // Записываем размеры матрицы
    file << rows << " " << cols << "\n";

    // Устанавливаем фиксированный формат с высокой точностью (например, 12 знаков после запятой)
    file << fixed << setprecision(12);

    // Записываем строки матрицы
    for (const auto& row : matrix) {
        for (size_t j = 0; j < row.size(); j++) {
            file << row[j];
            if (j != row.size() - 1) {
                file << " ";
            }
        }
        file << "\n";
    }

    file.close();
}

vector<vector<double>> readPGMToMatrix(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Open error!" << endl;
        return {};
    }

    string line;

    // Пропускаем первую строку (P2)
    getline(file, line);

    // Пропускаем комментарии и пустые строки, читаем размеры
    do {
        getline(file, line);
    } while (line.empty() || line[0] == '#');

    int cols, rows;
    stringstream dims(line);
    dims >> cols >> rows;

    //getline(file, line);

    // Читаем максимальное значение пикселя
    int maxVal;
    file >> maxVal;

    // Чтение пикселей
    vector<vector<double>> matrix(rows, vector<double>(cols));

    double pixel;
    //file >> pixel;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> pixel;
            matrix[i][j] = pixel;
        }
    }

    file.close();
    return matrix;
}

vector<vector<double>> readTIFFToMatrix(const string& filename) {
    GDALAllRegister();

    GDALDataset* poDataset = (GDALDataset*)GDALOpen(filename.c_str(), GA_ReadOnly);
    if (poDataset == nullptr) {
        cerr << "Cannot open TIFF: " << filename << endl;
        return {};
    }

    GDALRasterBand* poBand = poDataset->GetRasterBand(1);
    if (!poBand) {
        cerr << "Cannot get band 1." << endl;
        GDALClose(poDataset);
        return {};
    }

    int cols = poBand->GetXSize();
    int rows = poBand->GetYSize();

    vector<double> buffer(cols * rows);

    CPLErr err = poBand->RasterIO(
        GF_Read,
        0, 0,
        cols, rows,
        buffer.data(),
        cols, rows,
        GDT_Float64,
        0, 0
    );

    if (err != CE_None) {
        cerr << "RasterIO failed." << endl;
        GDALClose(poDataset);
        return {};
    }

    int hasNoData = 0;
    double noDataValue = poBand->GetNoDataValue(&hasNoData);

    vector<vector<double>> matrix(rows, vector<double>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double val = buffer[i * cols + j];
            if (hasNoData && val == noDataValue) {
                matrix[i][j] = std::numeric_limits<double>::quiet_NaN();
            }
            else {
                matrix[i][j] = val;
            }
        }
    }

    GDALClose(poDataset);
    return matrix;
}

vector<vector<int>> readTIFFToBinaryMatrix(const string& filename,
    uint8_t threshold = 128) {
    // Register GDAL drivers
    GDALAllRegister();

    // Open dataset
    GDALDataset* poDataset =
        (GDALDataset*)GDALOpen(filename.c_str(), GA_ReadOnly);
    if (!poDataset) {
        cerr << "Cannot open TIFF: " << filename << endl;
        return {};
    }

    // Take first band (for grayscale or RGB this is enough)
    GDALRasterBand* poBand = poDataset->GetRasterBand(1);
    if (!poBand) {
        cerr << "Cannot get band 1." << endl;
        GDALClose(poDataset);
        return {};
    }

    int cols = poBand->GetXSize();
    int rows = poBand->GetYSize();

    // Read data as 8-bit bytes (GDAL will convert internally if needed)
    vector<uint8_t> buffer(cols * rows);

    CPLErr err = poBand->RasterIO(
        GF_Read,
        0, 0,                 // x, y offset
        cols, rows,           // width, height to read
        buffer.data(),        // destination buffer
        cols, rows,           // buffer size
        GDT_Byte,             // type in buffer (0–255)
        0, 0                  // pixelSpace, lineSpace
    );

    if (err != CE_None) {
        cerr << "RasterIO failed." << endl;
        GDALClose(poDataset);
        return {};
    }

    // Create binary matrix: 1 for black, 0 for white
    vector<vector<int>> binary(rows, vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            uint8_t val = buffer[i * cols + j];

            // Typical case: black ≈ 0, white ≈ 255.
            // If pixel is darker than threshold -> mark as 1 (black).
            if (val <= threshold) {
                binary[i][j] = 0; // black
            }
            else {
                binary[i][j] = 1; // white
            }

            // If in твоём файле наоборот (white = 0, black = 255),
            // просто поменяй условие:
            // binary[i][j] = (val >= threshold) ? 1 : 0;
        }
    }

    GDALClose(poDataset);
    return binary;
}

vector<vector<double>> compareValues2(
    const vector<vector<double>>& matrixSolution,
    const vector<vector<double>>& matrixData,
    const vector<vector<double>>& inputMatrix
) {
    int rows = matrixSolution.size();
    int cols = matrixSolution[0].size();

    // 1) Copy inputMatrix into a new matrix
    vector<vector<double>> newMatrix = inputMatrix;

    // 2) Track the global minimum in newMatrix
    double minValue = 10000;
    double maxValue = 0;

    // 3) Single pass: adjust and update minValue
    int counter = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrixSolution[i][j] - matrixData[i][j] > 0) {
                newMatrix[i][j] = matrixData[i][j];
                counter++;
            }
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((newMatrix[i][j] < minValue) && newMatrix[i][j] != 0) {
                minValue = newMatrix[i][j];
            }
            if (newMatrix[i][j] > maxValue) {
                maxValue = newMatrix[i][j];
            }
        }
    }

    // 4) Print the minimum value in English
    cout << endl;
    cout << "Minimum value in new input matrix: " << minValue << endl;
    cout << "Max value in new input matrix: " << maxValue << endl;
    cout << "changes " << counter << endl;
    cout << "N: " << rows * cols << endl;
    return newMatrix;
}

vector<vector<double>> compareValues3( // if matrixSolution > ako DTM -> zapisat do tohto pixela DTM -> matrixSol after operation == next iter inputMatrix
    const vector<vector<double>>& matrixSolution,
    const vector<vector<double>>& matrixData
) {
    int rows = matrixSolution.size();
    int cols = matrixSolution[0].size();

    // 1) Copy inputMatrix into a new matrix
    vector<vector<double>> newMatrix = matrixSolution;

    // 2) Track the global minimum in newMatrix
    double minValue = 10000;
    double maxValue = 0;

    // 3) Single pass: adjust and update minValue
    int counter = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrixSolution[i][j] - matrixData[i][j] > 0) {
                newMatrix[i][j] = matrixData[i][j];
                counter++;
            }
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((newMatrix[i][j] < minValue) && newMatrix[i][j] != 0) {
                minValue = newMatrix[i][j];
            }
            if (newMatrix[i][j] > maxValue) {
                maxValue = newMatrix[i][j];
            }
        }
    }

    // 4) Print the minimum value in English
    cout << endl;
    cout << "Minimum value in edited solution matirx: " << minValue << endl;
    cout << "Max value in edited solution matirx: " << maxValue << endl;
    cout << "changes " << counter << endl;
    cout << "N: " << rows * cols << endl;

    return newMatrix;
}

vector<vector<double>> compareValues(vector<vector<double>>& matrixSolution, vector<vector<double>>& matrixData, double n) {

    int rows = matrixSolution.size();
    int cols = matrixSolution[0].size();


    vector<vector<double>> matrix(rows, vector<double>(cols));
    double difference;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            difference = matrixData[i][j] - matrixSolution[i][j];
            matrix[i][j] = (difference <= n && difference >= -1.0e-3) ? 1.0 : 0.0;
            //matrix[i][j] = (difference == 0) ? 1.0 : 0.0;
        }
    }

    return matrix;
}

vector<vector<double>> compareValuesV2(vector<vector<double>>& matrixSolution, vector<vector<double>>& matrixData, double n) {

    int rows = matrixSolution.size();
    int cols = matrixSolution[0].size();


    vector<vector<double>> matrix(rows, vector<double>(cols));
    double difference;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            //difference = matrixData[i][j] - matrixSolution[i][j];
            matrix[i][j] = (matrixSolution[i][j] >= (matrixData[i][j] - n)) ? 1.0 : 0.0;
            //matrix[i][j] = (difference == 0) ? 1.0 : 0.0;
        }
    }

    return matrix;
}

//int main() {
//
//    double a = 1;
//
//    int n = 1679;
//    int rows = n;
//    int cols = n;
//    int total_size = rows * cols;
//
//    vector<vector<double>> matrix(rows, vector<double>(cols));
//    double h = (a - 0.0) / (double)(n - 1);
//
//    int x1 = 5, y1_1 = 5, y1_2 = 20; // Начало прямых
//    int x2 = 25, y2_1 = 5, y2_2 = 20; // Конец прямых
//
//    // Узловые точки первой прямой
//    std::vector<std::pair<int, int>> line1 = bresenhamLine(x1, y1_1, x1, y1_2);
//    // Узловые точки второй прямой
//   // std::vector<std::pair<int, int>> line2 = bresenhamLine(x2, y2_1, x2, y2_2);
//
//
//    //std::ofstream file("lines.txt");
//    //if (!file.is_open()) {
//    //    std::cerr << "Error opening file for writing!" << std::endl;
//    //    return 1;
//    //}
//
//    //file << "(* First Line *)\n";
//    //file << "line1 = {";
//    //for (size_t i = 0; i < line1.size(); ++i) {
//    //    file << "{" << line1[i].first << ", " << line1[i].second << "}";
//    //    if (i != line1.size() - 1) file << ", ";
//    //}
//    //file << "};\n";
//
//    // Записываем точки второй прямой в файл
//    /*file << "(* Second Line *)\n";
//    file << "line2 = {";
//    for (size_t i = 0; i < line2.size(); ++i) {
//        file << "{" << line2[i].first << ", " << line2[i].second << "}";
//        if (i != line2.size() - 1) file << ", ";
//    }
//    file << "};\n";*/
//
//    // Добавляем команду для построения графика в Wolfram Mathematica
//    //file << "\nListPlot[{line1, line2}, PlotStyle -> {Red, Blue}, "
//    //    << "Joined -> True, AspectRatio -> Automatic, "
//    //    << "AxesLabel -> {\"x\", \"y\"}, PlotMarkers -> Automatic];\n";
//
//    //// Закрываем файл
//    //file.close();
//
//    vector<vector<double>> inputMatrix;
//    //string filename = "inputForSolveMembr2.txt";  // Specify your input file name here 
//    string filename = "inputForSolveMembrTestObr21AfterEraseV2Ostacle1V2.txt";
//    //string filename = "inputForSolveMembrTestObr21AfterEraseV2.txt";
//
//
//    matrix = loadMatrixFromFile(filename);
//
//    double minValue = 200;
//    double maxValue = matrix[0][0];
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            if ((i == 0 && j == 0) || matrix[i][j] == 0) {
//                continue;
//            }
//            else {
//                if (minValue > matrix[i][j])
//                    minValue = matrix[i][j];
//                if (maxValue < matrix[i][j])
//                    maxValue = matrix[i][j];
//            }
//
//        }
//    }
//
//    cout << minValue << " " << maxValue << endl;
//
//    /*vector<vector<double>> differnce = compareValues(inputMatrix, inputMatrix);
//
//    saveMatrixToPGM(inputMatrix, "matInput.pgm");
//
//    cout << "diff end" << endl;
//    saveMatrixToPGM(differnce, "diffInput.pgm");
//    cout << "diff end" << endl;*/
//    // Call the function to solve the membrane system
//
//    //std::vector<std::pair<int, int>> points = bresenhamLine(x1, y1, x2, y2);
//
//
//    //for (int i = 0; i < rows; i++) {
//    //    for (int j = 0; j < cols; j++) {
//    //        if (i == 0) {
//    //            //matrix[i][j] = g(j * h);
//    //            matrix[i][j] = 0;
//    //        }
//    //        else if (j == 0) {
//    //            //matrix[i][j] = g(i * h);
//    //            matrix[i][j] = 0;
//    //        }
//    //        else if (i == n - 1) {
//    //            //matrix[i][j] = g(j * h);
//    //            matrix[i][j] = 0;
//    //        }
//    //        else if (j == n - 1) {
//    //            //matrix[i][j] = g(i * h);
//    //            matrix[i][j] = 0;
//
//    //        }
//    //        else {
//    //            matrix[i][j] = 100.0;
//    //        }
//    //        //matrix[i][j] = 100.0;
//    //    }
//    //}
//
//    //for (const auto& point : line1) {
//    //    int x = point.first;
//    //    int y = point.second;
//    //    if (x >= 0 && x < 30 && y >= 0 && y < n) {
//    //        matrix[x][y] = 10; // Учитываем, что y — строка, x — столбец
//    //    }
//    //}
//
//    /*for (const auto& point : line2) {
//        int x = point.first;
//        int y = point.second;
//        if (x >= 0 && x < n && y >= 0 && y < n) {
//            matrix[x][y] = 0;
//        }
//    }*/
//
//    
//    //Eigen::initParallel();
//    SparseMatrix<double> A(n * n, n * n);
//    SparseMatrix<double> temp(n * n, n * n);
//    VectorXd b(n * n), x(n * n);
//
//    A.reserve(Eigen::VectorXi::Constant(n * n, 5));
//
//#pragma omp parallel for
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            int idx = i * cols + j;
//            if (matrix[i][j] != 0) {
//                A.insert(idx, idx) = 1.0;
//                b(idx) = matrix[i][j];
//            }
//            else {
//                A.insert(idx, idx) = 4.0;
//                if (j + 1 > cols - 1) { //2
//                    if (i - 1 < 0) { //5
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (i + 1 > rows - 1) { //6
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx - cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    A.insert(idx, idx - 1) = -2.0;
//                    A.insert(idx, idx + cols) = -1.0;
//                    A.insert(idx, idx - cols) = -1.0;
//                    b(idx) = 0.0;
//                    continue;
//                }
//                if (i - 1 < 0) { // 1
//                    if (j + 1 > cols - 1) { // 5
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (j - 1 < 0) { //8
//                        A.insert(idx, idx + 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    A.insert(idx, idx - 1) = -1.0;
//                    A.insert(idx, idx + cols) = -2.0;
//                    A.insert(idx, idx + 1) = -1.0;
//                    b(idx) = 0.0;
//                    continue;
//                }
//                if (j - 1 < 0) { //4
//                    if (i - 1 < 0) { //8
//                        A.insert(idx, idx + 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (i + 1 > rows - 1) { //7
//                        A.insert(idx, idx - cols) = -2.0;
//                        A.insert(idx, idx + 1) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    A.insert(idx, idx - cols) = -1.0;
//                    A.insert(idx, idx + cols) = -1.0;
//                    A.insert(idx, idx + 1) = -2.0;
//                    b(idx) = 0.0;
//                    continue;
//                }
//                if (i + 1 > rows - 1) { // 3
//                    if (j - 1 < 0) { // 7
//                        A.insert(idx, idx - cols) = -2.0;
//                        A.insert(idx, idx + 1) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (j + 1 > cols - 1) { //6
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx - cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    A.insert(idx, idx - cols) = -2.0;
//                    A.insert(idx, idx - 1) = -1.0;
//                    A.insert(idx, idx + 1) = -1.0;
//                    b(idx) = 0.0;
//                    continue;
//                }
//                A.insert(idx, idx + 1) = -1.0;//i,j+1
//                A.insert(idx, idx - 1) = -1.0;//i,j-1
//                A.insert(idx, idx + cols) = -1.0;//i+1,j
//                A.insert(idx, idx - cols) = -1.0;//i-1,j
//                b(idx) = 0.0;
//            }
//        }
//    }
//
//    /*for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            if (i == 0) {
//                A.insert(j, j) = 1.0;
//                b(j) = g(j * h);
//            }
//            else if (j == 0) {
//                A.insert(i * n, i * n) = 1.0;
//                b(i * n) = g(i * h);
//            }
//            else if (i == n - 1) {
//                A.insert(i * n + j, i * n + j) = 1.0;
//                b(i * n + j) = g(j * h);
//            }
//            else if (j == n - 1) {
//                A.insert(i * n + j, i * n + j) = 1.0;
//                b(i * n + j) = g(i * h);
//            }
//            else {
//                A.insert(i * n + j, i * n + j) = 4.0;
//                A.insert(i * n + j, i * n + j + 1) = -1.0;
//                A.insert(i * n + j, i * n + j - 1) = -1.0;
//                A.insert(i * n + j, (i + 1) * n + j) = -1.0;
//                A.insert(i * n + j, (i - 1) * n + j) = -1.0;
//                b(i * n + j) = 0.0;
//            }
//        }
//    }*/
//    temp = A;
//    A.makeCompressed();
//    BiCGSTAB<SparseMatrix<double>> solver;
//    solver.compute(A);
//    x = solver.solve(b);
//
//    vector<vector<double>> matrixFinal(rows, vector<double>(cols));
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            matrixFinal[i][j] = x(i * cols + j);
//        }
//    }
//
//    minValue = matrixFinal[0][0];
//    maxValue = matrixFinal[0][0];
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            if ((i == 0 && j == 0) || matrixFinal[i][j] == 0) {
//                continue;
//            }
//            else {
//                if (minValue > matrixFinal[i][j])
//                    minValue = matrixFinal[i][j];
//                if (maxValue < matrixFinal[i][j])
//                    maxValue = matrixFinal[i][j];
//            }
//
//        }
//    }
//
//    cout << minValue << " " << maxValue << endl;
//
//    double L2Norm = 0.0;
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            L2Norm += h * h * matrixFinal[i][j] * matrixFinal[i][j];
//        }
//    }
//
//    double tL2 = sqrt(L2Norm);
//    L2Norm = tL2;
//    cout << endl;
//    cout << L2Norm << endl;
//
//    double xMin = 0.0, xMax = 30.0;
//    double yMin = 0.0, yMax = 30.0;
//
//    ofstream file;
//    file.open("solutionWatersSept.txt", ios::out);
//
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            file << i * h << " " << j * h << " " << x(i * n + j) << endl;
//        }
//    }
//
//    file.close();
//
//    saveMatrixToPGM(matrixFinal, "solutionWatersSept.txt.pgm");
//
//    saveMatrixToFile(matrixFinal, "solutionWatersSept.txt.txt");
//
//    //printMatrix(matrix);
//
//    double sum = 0.0;
//
//    return 0;
//}

//int main() {
//
//    double a = 1;
//
//    int n = 1679;
//    int rows = n;
//    int cols = n;
//    int total_size = rows * cols;
//
//    vector<vector<double>> matrix(rows, vector<double>(cols));
//    double h = (a - 0.0) / (double)(n - 1);
//
//    int x1 = 5, y1_1 = 5, y1_2 = 20; // Начало прямых
//    int x2 = 25, y2_1 = 5, y2_2 = 20; // Конец прямых
//
//    // Узловые точки первой прямой
//    std::vector<std::pair<int, int>> line1 = bresenhamLine(x1, y1_1, x1, y1_2);
//
//    // Узловые точки второй прямой
//   // std::vector<std::pair<int, int>> line2 = bresenhamLine(x2, y2_1, x2, y2_2);
//
//
//    //std::ofstream file("lines.txt");
//    //if (!file.is_open()) {
//    //    std::cerr << "Error opening file for writing!" << std::endl;
//    //    return 1;
//    //}
//
//    //file << "(* First Line *)\n";
//    //file << "line1 = {";
//    //for (size_t i = 0; i < line1.size(); ++i) {
//    //    file << "{" << line1[i].first << ", " << line1[i].second << "}";
//    //    if (i != line1.size() - 1) file << ", ";
//    //}
//    //file << "};\n";
//
//    // Записываем точки второй прямой в файл
//    /*file << "(* Second Line *)\n";
//    file << "line2 = {";
//    for (size_t i = 0; i < line2.size(); ++i) {
//        file << "{" << line2[i].first << ", " << line2[i].second << "}";
//        if (i != line2.size() - 1) file << ", ";
//    }
//    file << "};\n";*/
//
//    // Добавляем команду для построения графика в Wolfram Mathematica
//    //file << "\nListPlot[{line1, line2}, PlotStyle -> {Red, Blue}, "
//    //    << "Joined -> True, AspectRatio -> Automatic, "
//    //    << "AxesLabel -> {\"x\", \"y\"}, PlotMarkers -> Automatic];\n";
//
//    //// Закрываем файл
//    //file.close();
//
//
//
//    vector<vector<double>> inputMatrix;
//    //string filename = "inputForSolveMembr2.txt";  // Specify your input file name here 
//    //string filename = "inputForSolveMembrTestObr21AfterEraseV2Ostacle1V2.txt";
//    string filename = "inputForSolveMembrTestObr21AfterEraseV2.txt";
//    //string filename = "inputForSolveMembrIter1Sept.txt";
//
//    matrix = loadMatrixFromFile(filename);
//
//    filename = "Hores_square_DTM_data.pgm";
//
//    vector<vector<double>> downloadedMatrixData = readPGMToMatrix(filename);
//
//    double minValue = 200;
//    double maxValue = matrix[0][0];
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            if ((i == 0 && j == 0) || matrix[i][j] == 0) {
//                continue;
//            }
//            else {
//                if (minValue > matrix[i][j])
//                    minValue = matrix[i][j];
//                if (maxValue < matrix[i][j])
//                    maxValue = matrix[i][j];
//            }
//
//        }
//    }
//    
//    cout << "min and max value input matrix:" << endl;
//    cout << minValue << " " << maxValue << endl;
//
//    /*vector<vector<double>> differnce = compareValues(inputMatrix, inputMatrix);
//
//    saveMatrixToPGM(inputMatrix, "matInput.pgm");
//
//    cout << "diff end" << endl;
//    saveMatrixToPGM(differnce, "diffInput.pgm");
//    cout << "diff end" << endl;*/
//    // Call the function to solve the membrane system
//
//    //std::vector<std::pair<int, int>> points = bresenhamLine(x1, y1, x2, y2);
//
//
//    //for (int i = 0; i < rows; i++) {
//    //    for (int j = 0; j < cols; j++) {
//    //        if (i == 0) {
//    //            //matrix[i][j] = g(j * h);
//    //            matrix[i][j] = 0;
//    //        }
//    //        else if (j == 0) {
//    //            //matrix[i][j] = g(i * h);
//    //            matrix[i][j] = 0;
//    //        }
//    //        else if (i == n - 1) {
//    //            //matrix[i][j] = g(j * h);
//    //            matrix[i][j] = 0;
//    //        }
//    //        else if (j == n - 1) {
//    //            //matrix[i][j] = g(i * h);
//    //            matrix[i][j] = 0;
//
//    //        }
//    //        else {
//    //            matrix[i][j] = 100.0;
//    //        }
//    //        //matrix[i][j] = 100.0;
//    //    }
//    //}
//
//    //for (const auto& point : line1) {
//    //    int x = point.first;
//    //    int y = point.second;
//    //    if (x >= 0 && x < 30 && y >= 0 && y < n) {
//    //        matrix[x][y] = 10; // Учитываем, что y — строка, x — столбец
//    //    }
//    //}
//
//    /*for (const auto& point : line2) {
//        int x = point.first;
//        int y = point.second;
//        if (x >= 0 && x < n && y >= 0 && y < n) {
//            matrix[x][y] = 0;
//        }
//    }*/
//
//
//    //Eigen::initParallel();
//    SparseMatrix<double> A(n * n, n * n);
//    SparseMatrix<double> temp(n * n, n * n);
//    VectorXd b(n * n), x(n * n);
//
//    A.reserve(Eigen::VectorXi::Constant(n * n, 5));
//
//#pragma omp parallel for
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            int idx = i * cols + j;
//            if (matrix[i][j] != 0) {
//                A.insert(idx, idx) = 1.0;
//                b(idx) = matrix[i][j];
//            }
//            else {
//                A.insert(idx, idx) = 4.0;
//                if (j + 1 > cols - 1) { //2
//                    if (i - 1 < 0) { //5
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        //b(idx) = downloadedMatrixData[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    if (i + 1 > rows - 1) { //6
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx - cols) = -2.0;
//                        //b(idx) = downloadedMatrixData[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    A.insert(idx, idx - 1) = -2.0;
//                    A.insert(idx, idx + cols) = -1.0;
//                    A.insert(idx, idx - cols) = -1.0;
//                    //b(idx) = downloadedMatrixData[i][j];
//                    b(idx) = 0;
//                    continue;
//                }
//                if (i - 1 < 0) { // 1
//                    if (j + 1 > cols - 1) { // 5
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        //b(idx) = downloadedMatrixData[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    if (j - 1 < 0) { //8
//                        A.insert(idx, idx + 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        //b(idx) = downloadedMatrixData[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    A.insert(idx, idx - 1) = -1.0;
//                    A.insert(idx, idx + cols) = -2.0;
//                    A.insert(idx, idx + 1) = -1.0;
//                    //b(idx) = downloadedMatrixData[i][j];
//                    b(idx) = 0;
//                    continue;
//                }
//                if (j - 1 < 0) { //4
//                    if (i - 1 < 0) { //8
//                        A.insert(idx, idx + 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        //b(idx) = downloadedMatrixData[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    if (i + 1 > rows - 1) { //7
//                        A.insert(idx, idx - cols) = -2.0;
//                        A.insert(idx, idx + 1) = -2.0;
//                       //b(idx) = downloadedMatrixData[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    A.insert(idx, idx - cols) = -1.0;
//                    A.insert(idx, idx + cols) = -1.0;
//                    A.insert(idx, idx + 1) = -2.0;
//                    //b(idx) = downloadedMatrixData[i][j];
//                    b(idx) = 0;
//                    continue;
//                }
//                if (i + 1 > rows - 1) { // 3
//                    if (j - 1 < 0) { // 7
//                        A.insert(idx, idx - cols) = -2.0;
//                        A.insert(idx, idx + 1) = -2.0;
//                        //b(idx) = downloadedMatrixData[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    if (j + 1 > cols - 1) { //6
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx - cols) = -2.0;
//                        //b(idx) = downloadedMatrixData[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    A.insert(idx, idx - cols) = -2.0;
//                    A.insert(idx, idx - 1) = -1.0;
//                    A.insert(idx, idx + 1) = -1.0;
//                    //b(idx) = downloadedMatrixData[i][j];
//                    b(idx) = 0;
//                    continue;
//                }
//                A.insert(idx, idx + 1) = -1.0;//i,j+1
//                A.insert(idx, idx - 1) = -1.0;//i,j-1
//                A.insert(idx, idx + cols) = -1.0;//i+1,j
//                A.insert(idx, idx - cols) = -1.0;//i-1,j
//                //b(idx) = downloadedMatrixData[i][j];
//                b(idx) = 0;
//            }
//        }
//    }
//
//    /*for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            if (i == 0) {
//                A.insert(j, j) = 1.0;
//                b(j) = g(j * h);
//            }
//            else if (j == 0) {
//                A.insert(i * n, i * n) = 1.0;
//                b(i * n) = g(i * h);
//            }
//            else if (i == n - 1) {
//                A.insert(i * n + j, i * n + j) = 1.0;
//                b(i * n + j) = g(j * h);
//            }
//            else if (j == n - 1) {
//                A.insert(i * n + j, i * n + j) = 1.0;
//                b(i * n + j) = g(i * h);
//            }
//            else {
//                A.insert(i * n + j, i * n + j) = 4.0;
//                A.insert(i * n + j, i * n + j + 1) = -1.0;
//                A.insert(i * n + j, i * n + j - 1) = -1.0;
//                A.insert(i * n + j, (i + 1) * n + j) = -1.0;
//                A.insert(i * n + j, (i - 1) * n + j) = -1.0;
//                b(i * n + j) = 0.0;
//            }
//        }
//    }*/
//    temp = A;
//    A.makeCompressed();
//    BiCGSTAB<SparseMatrix<double>> solver;
//    solver.compute(A);
//    x = solver.solve(b);
//
//    vector<vector<double>> matrixFinal(rows, vector<double>(cols));
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            matrixFinal[i][j] = x(i * cols + j);
//        }
//    }
//
//    minValue = 1000;
//    maxValue = 0;
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            if ((i == 0 && j == 0) || matrixFinal[i][j] == 0) {
//                continue;
//            }
//            else {
//                if (minValue > matrixFinal[i][j])
//                    minValue = matrixFinal[i][j];
//                if (maxValue < matrixFinal[i][j])
//                    maxValue = matrixFinal[i][j];
//            }
//
//        }
//    }
//
//
//    cout << "min and max value solution iter 0:" << endl;
//    cout << minValue << " " << maxValue << endl;
//
//    double L2Norm = 0.0;
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            L2Norm += h * h * matrixFinal[i][j] * matrixFinal[i][j];
//        }
//    }
//
//    double tL2 = sqrt(L2Norm);
//    L2Norm = tL2;
//    cout << endl;
//    cout << "L2 norma" << L2Norm << endl;
//
//    double xMin = 0.0, xMax = 30.0;
//    double yMin = 0.0, yMax = 30.0;
//
//    ofstream file;
//    //file.open("solutionWatersSeptZacatPodmienkDTM.txt", ios::out);
//    file.open("solutionWatersSept.txt", ios::out);
//
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            file << i * h << " " << j * h << " " << x(i * n + j) << endl;
//        }
//    }
//
//    file.close();
//
//    saveMatrixToPGM(matrixFinal, "solutionWatersSept.pgm");
//
//    saveMatrixToFile(matrixFinal, "solutionWatersSept.txt");
//
//    //printMatrix(matrix);
//
//    double sum = 0.0;
//
//    /*filename = "Hores_square_DTM_data.pgm";
//
//    vector<vector<double>> downloadedMatrixData = readPGMToMatrix(filename);*/
//
//    vector<vector<double>> matrixIter1 = compareValues2(matrixFinal, downloadedMatrixData, matrix);
//
//    //matrix = loadMatrixFromFile(filename);
//
//    minValue = 200;
//    maxValue = matrixIter1[0][0];
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            if (matrixIter1[i][j] == 0) {
//                continue;
//            }
//            else {
//                if (minValue > matrixIter1[i][j])
//                    minValue = matrixIter1[i][j];
//                if (maxValue < matrixIter1[i][j])
//                    maxValue = matrixIter1[i][j];
//            }
//
//        }
//    }
//
//    cout << "min and max value input matrix Iter1:" << endl;
//    cout << minValue << " " << maxValue << endl;
//
//    /*vector<vector<double>> differnce = compareValues(inputMatrix, inputMatrix);
//
//    saveMatrixToPGM(inputMatrix, "matInput.pgm");
//
//    cout << "diff end" << endl;
//    saveMatrixToPGM(differnce, "diffInput.pgm");
//    cout << "diff end" << endl;*/
//    // Call the function to solve the membrane system
//
//    //std::vector<std::pair<int, int>> points = bresenhamLine(x1, y1, x2, y2);
//
//
//    //for (int i = 0; i < rows; i++) {
//    //    for (int j = 0; j < cols; j++) {
//    //        if (i == 0) {
//    //            //matrix[i][j] = g(j * h);
//    //            matrix[i][j] = 0;
//    //        }
//    //        else if (j == 0) {
//    //            //matrix[i][j] = g(i * h);
//    //            matrix[i][j] = 0;
//    //        }
//    //        else if (i == n - 1) {
//    //            //matrix[i][j] = g(j * h);
//    //            matrix[i][j] = 0;
//    //        }
//    //        else if (j == n - 1) {
//    //            //matrix[i][j] = g(i * h);
//    //            matrix[i][j] = 0;
//
//    //        }
//    //        else {
//    //            matrix[i][j] = 100.0;
//    //        }
//    //        //matrix[i][j] = 100.0;
//    //    }
//    //}
//
//    //for (const auto& point : line1) {
//    //    int x = point.first;
//    //    int y = point.second;
//    //    if (x >= 0 && x < 30 && y >= 0 && y < n) {
//    //        matrix[x][y] = 10; // Учитываем, что y — строка, x — столбец
//    //    }
//    //}
//
//    /*for (const auto& point : line2) {
//        int x = point.first;
//        int y = point.second;
//        if (x >= 0 && x < n && y >= 0 && y < n) {
//            matrix[x][y] = 0;
//        }
//    }*/
//
//
//    Eigen::initParallel();
//    //SparseMatrix<double> A(n * n, n * n);
//    //SparseMatrix<double> temp(n * n, n * n);
//    //VectorXd b(n * n), x(n * n);
//
//
//    A.resize(n* n, n* n);
//    temp.resize(n * n, n*n);
//    b.resize(n * n);
//    x.resize(n * n);
//
//    //h = (a - 0.0) / (double)(rows - 1);
//
//    //A.reserve(Eigen::VectorXi::Constant(n* n, 5));
//
//
//    A.reserve(Eigen::VectorXi::Constant(n * n, 5));
//
//#pragma omp parallel for
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            int idx = i * cols + j;
//            if (matrixIter1[i][j] != 0) {
//                A.insert(idx, idx) = 1.0;
//                b(idx) = matrixIter1[i][j];
//            }
//            else {
//                A.insert(idx, idx) = 4.0;
//                if (j + 1 > cols - 1) { //2
//                    if (i - 1 < 0) { //5
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        //b(idx) = matrixFinal[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    if (i + 1 > rows - 1) { //6
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx - cols) = -2.0;
//                        //b(idx) = matrixFinal[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    A.insert(idx, idx - 1) = -2.0;
//                    A.insert(idx, idx + cols) = -1.0;
//                    A.insert(idx, idx - cols) = -1.0;
//                    //b(idx) = matrixFinal[i][j];
//                    b(idx) = 0;
//                    continue;
//                }
//                if (i - 1 < 0) { // 1
//                    if (j + 1 > cols - 1) { // 5
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        //b(idx) = matrixFinal[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    if (j - 1 < 0) { //8
//                        A.insert(idx, idx + 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        //b(idx) = matrixFinal[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    A.insert(idx, idx - 1) = -1.0;
//                    A.insert(idx, idx + cols) = -2.0;
//                    A.insert(idx, idx + 1) = -1.0;
//                    //b(idx) = matrixFinal[i][j];
//                    b(idx) = 0;
//                    continue;
//                }
//                if (j - 1 < 0) { //4
//                    if (i - 1 < 0) { //8
//                        A.insert(idx, idx + 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        //b(idx) = matrixFinal[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    if (i + 1 > rows - 1) { //7
//                        A.insert(idx, idx - cols) = -2.0;
//                        A.insert(idx, idx + 1) = -2.0;
//                        //b(idx) = matrixFinal[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    A.insert(idx, idx - cols) = -1.0;
//                    A.insert(idx, idx + cols) = -1.0;
//                    A.insert(idx, idx + 1) = -2.0;
//                    //b(idx) = matrixFinal[i][j];
//                    b(idx) = 0;
//                    continue;
//                }
//                if (i + 1 > rows - 1) { // 3
//                    if (j - 1 < 0) { // 7
//                        A.insert(idx, idx - cols) = -2.0;
//                        A.insert(idx, idx + 1) = -2.0;
//                        //b(idx) = matrixFinal[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    if (j + 1 > cols - 1) { //6
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx - cols) = -2.0;
//                        //b(idx) = matrixFinal[i][j];
//                        b(idx) = 0;
//                        continue;
//                    }
//                    A.insert(idx, idx - cols) = -2.0;
//                    A.insert(idx, idx - 1) = -1.0;
//                    A.insert(idx, idx + 1) = -1.0;
//                    //b(idx) = matrixFinal[i][j];
//                    b(idx) = 0;
//                    continue;
//                }
//                A.insert(idx, idx + 1) = -1.0;//i,j+1
//                A.insert(idx, idx - 1) = -1.0;//i,j-1
//                A.insert(idx, idx + cols) = -1.0;//i+1,j
//                A.insert(idx, idx - cols) = -1.0;//i-1,j
//                //b(idx) = matrixFinal[i][j];
//                b(idx) = 0;
//            }
//        }
//    }
//
//    /*for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            if (i == 0) {
//                A.insert(j, j) = 1.0;
//                b(j) = g(j * h);
//            }
//            else if (j == 0) {
//                A.insert(i * n, i * n) = 1.0;
//                b(i * n) = g(i * h);
//            }
//            else if (i == n - 1) {
//                A.insert(i * n + j, i * n + j) = 1.0;
//                b(i * n + j) = g(j * h);
//            }
//            else if (j == n - 1) {
//                A.insert(i * n + j, i * n + j) = 1.0;
//                b(i * n + j) = g(i * h);
//            }
//            else {
//                A.insert(i * n + j, i * n + j) = 4.0;
//                A.insert(i * n + j, i * n + j + 1) = -1.0;
//                A.insert(i * n + j, i * n + j - 1) = -1.0;
//                A.insert(i * n + j, (i + 1) * n + j) = -1.0;
//                A.insert(i * n + j, (i - 1) * n + j) = -1.0;
//                b(i * n + j) = 0.0;
//            }
//        }
//    }*/
//    temp = A;
//    A.makeCompressed();
//    BiCGSTAB<SparseMatrix<double>> solverIter1;
//    solverIter1.compute(A);
//    VectorXd xIter1(n* n);
//    xIter1 = solverIter1.solve(b);
//
//    vector<vector<double>> matrixFinalIter1(rows, vector<double>(cols));
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            matrixFinalIter1[i][j] = xIter1(i * cols + j);
//        }
//    }
//
//    
//    minValue = 10000;
//    maxValue = 0;
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            if (matrixFinalIter1[i][j] == 0) {
//                continue;
//            }
//            else {
//                if (minValue > matrixFinalIter1[i][j])
//                    minValue = matrixFinalIter1[i][j];
//                if (maxValue < matrixFinalIter1[i][j])
//                    maxValue = matrixFinalIter1[i][j];
//            }
//
//        }
//    }
//
//    cout << endl;
//    cout << "min and max value solution after Iter1:" << endl;
//    cout << minValue << " " << maxValue << endl;
//
//    L2Norm = 0.0;
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            L2Norm += h * h * matrixFinalIter1[i][j] * matrixFinalIter1[i][j];
//        }
//    }
//
//    tL2 = sqrt(L2Norm);
//    L2Norm = tL2;
//    cout << endl;
//    cout << "L2 norm solution after Iter1 " << L2Norm << endl;
//
//    /*ofstream file;
//    file.open("solutionWatersSept.txt", ios::out);
//
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            file << i * h << " " << j * h << " " << x(i * n + j) << endl;
//        }
//    }
//
//    file.close();*/
//
//    vector<vector<double>> matrixIter2 = compareValues2(matrixFinalIter1, downloadedMatrixData, matrixIter1);
//
//    int counter = 0;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            if (fabs(matrixFinalIter1[i][j] - matrixFinal[i][j]) > 0.000001)
//                counter++;
//        }
//    }
//
//    cout << "dif pixels:" << counter << endl;
//
//    file.open("solutionWatersSeptIter1.txt", ios::out);
//
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            file << i * h << " " << j * h << " " << xIter1(i * n + j) << endl;
//        }
//    }
//
//    file.close();
//
//    saveMatrixToPGM(matrixFinalIter1, "solutionWatersSeptIter1.pgm");
//
//    saveMatrixToFile(matrixFinalIter1, "solutionWatersSeptIter1.txt");
//
//    return 0;
//}

VectorXd solveSchemeLaplace(vector<vector<double>> matrix, vector<vector<double>> dtmStart, int r, int c) {
    int rows = r;
    int cols = c;
    int total_size = rows * cols;

    SparseMatrix<double> A(r * c, r * c);
    SparseMatrix<double> temp(r * c, r * c);
    VectorXd b(r * c), x(r * c);

    A.reserve(Eigen::VectorXi::Constant(r * c, 5));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int idx = i * cols + j;
            if (matrix[i][j] != 0) {
                A.insert(idx, idx) = 1.0;
                b(idx) = dtmStart[i][j];
            }
            else {
                A.insert(idx, idx) = 4;
                if (j + 1 > cols - 1) { //2
                    if (i - 1 < 0) { //5
                        A.insert(idx, idx - 1) = -2.0;
                        A.insert(idx, idx + cols) = -2.0;
                        //b(idx) = matrixInPrevTime[i][j];
                        b(idx) = 0;
                        continue;
                    }
                    if (i + 1 > rows - 1) { //6
                        A.insert(idx, idx - 1) = -2.0;
                        A.insert(idx, idx - cols) = -2.0;
                        //b(idx) = matrixInPrevTime[i][j];
                        b(idx) = 0;
                        continue;
                    }
                    A.insert(idx, idx - 1) = -2.0;
                    A.insert(idx, idx + cols) = -1.0;
                    A.insert(idx, idx - cols) = -1.0;
                    //b(idx) = matrixInPrevTime[i][j];
                    b(idx) = 0;
                    continue;
                }
                if (i - 1 < 0) { // 1
                    if (j + 1 > cols - 1) { // 5
                        A.insert(idx, idx - 1) = -2.0;
                        A.insert(idx, idx + cols) = -2.0;
                        //b(idx) = matrixInPrevTime[i][j];
                        b(idx) = 0;
                        continue;
                    }
                    if (j - 1 < 0) { //8
                        A.insert(idx, idx + 1) = -2.0;
                        A.insert(idx, idx + cols) = -2.0;
                        //b(idx) = matrixInPrevTime[i][j];
                        b(idx) = 0;
                        continue;
                    }
                    A.insert(idx, idx - 1) = -1.0;
                    A.insert(idx, idx + cols) = -2.0;
                    A.insert(idx, idx + 1) = -1.0;
                    //b(idx) = matrixInPrevTime[i][j];
                    b(idx) = 0;
                    continue;
                }
                if (j - 1 < 0) { //4
                    if (i - 1 < 0) { //8
                        A.insert(idx, idx + 1) = -2.0;
                        A.insert(idx, idx + cols) = -2.0;
                        //b(idx) = matrixInPrevTime[i][j];
                        b(idx) = 0;
                        continue;
                    }
                    if (i + 1 > rows - 1) { //7
                        A.insert(idx, idx - cols) = -2.0;
                        A.insert(idx, idx + 1) = -2.0;
                        //b(idx) = matrixInPrevTime[i][j];
                        b(idx) = 0;
                        continue;
                    }
                    A.insert(idx, idx - cols) = -1.0;
                    A.insert(idx, idx + cols) = -1.0;
                    A.insert(idx, idx + 1) = -2.0;
                    //b(idx) = matrixInPrevTime[i][j];
                    b(idx) = 0;
                    continue;
                }
                if (i + 1 > rows - 1) { // 3
                    if (j - 1 < 0) { // 7
                        A.insert(idx, idx - cols) = -2.0;
                        A.insert(idx, idx + 1) = -2.0;
                        //b(idx) = matrixInPrevTime[i][j];
                        b(idx) = 0;
                        continue;
                    }
                    if (j + 1 > cols - 1) { //6
                        A.insert(idx, idx - 1) = -2.0;
                        A.insert(idx, idx - cols) = -2.0;
                        //b(idx) = matrixInPrevTime[i][j];
                        b(idx) = 0;
                        continue;
                    }
                    A.insert(idx, idx - cols) = -2.0;
                    A.insert(idx, idx - 1) = -1.0;
                    A.insert(idx, idx + 1) = -1.0;
                    //b(idx) = matrixInPrevTime[i][j];
                    b(idx) = 0;
                    continue;
                }
                A.insert(idx, idx + 1) = -1.0;//i,j+1
                A.insert(idx, idx - 1) = -1.0;//i,j-1
                A.insert(idx, idx + cols) = -1.0;//i+1,j
                A.insert(idx, idx - cols) = -1.0;//i-1,j
                //b(idx) = matrixInPrevTime[i][j];
                b(idx) = 0;
            }
        }
    }

    temp = A;
    A.makeCompressed();
    BiCGSTAB<SparseMatrix<double>> solver;
    solver.compute(A);
    x = solver.solve(b);

    return x;
}

void saveTXTFor3D(vector<vector<double>> matrixSol, int n, double h, int iter) {
    ofstream file;
    //std::string filenameCurrentTXT = "SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifMinHores1515ByFunc" + std::to_string(iter) + "ForWolfram.txt";
    //std::string filenameCurrentTXT = "SinXSin3GSV2Iter" + std::to_string(iter) + "ForWolfram.txt";
    std::string filenameCurrentTXT = "SinXSin3PSORV2Iter" + std::to_string(iter) + "ForWolfram.txt";
    //std::string filenameCurrentTXT = "Real2PSORV2Iter" + std::to_string(iter) + "ForWolfram.txt";

    file.open(filenameCurrentTXT, ios::out);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file << i << " " << j << " " << matrixSol[i][j] << endl;
        }
    }

    file.close();
}

//VectorXd solveSchemeGS(vector<vector<double>> matrix, vector<vector<double>> dtmStart, int r, int c) {
//    int rows = r;
//    int cols = c;
//    int total_size = rows * cols;
//
//    SparseMatrix<double> A(r * c, r * c);
//    VectorXd b(r * c), x(r * c), x_old(r * c);
//
//    A.reserve(Eigen::VectorXi::Constant(r * c, 5));
//
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            int idx = i * cols + j;
//            if (matrix[i][j] != 0) {
//                A.insert(idx, idx) = 1.0;
//                b(idx) = dtmStart[i][j];
//            }
//            else {
//                A.insert(idx, idx) = 4.0;
//
//                if (j + 1 > cols - 1) { //2
//                    if (i - 1 < 0) { //5
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (i + 1 > rows - 1) { //6
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx - cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    A.insert(idx, idx - 1) = -2.0;
//                    A.insert(idx, idx + cols) = -1.0;
//                    A.insert(idx, idx - cols) = -1.0;
//                    b(idx) = 0.0;
//                    continue;
//                }
//
//                if (i - 1 < 0) { //1
//                    if (j + 1 > cols - 1) { //5
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (j - 1 < 0) { //8
//                        A.insert(idx, idx + 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    A.insert(idx, idx - 1) = -1.0;
//                    A.insert(idx, idx + cols) = -2.0;
//                    A.insert(idx, idx + 1) = -1.0;
//                    b(idx) = 0.0;
//                    continue;
//                }
//
//                if (j - 1 < 0) { //4
//                    if (i - 1 < 0) { //8
//                        A.insert(idx, idx + 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (i + 1 > rows - 1) { //7
//                        A.insert(idx, idx - cols) = -2.0;
//                        A.insert(idx, idx + 1) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    A.insert(idx, idx - cols) = -1.0;
//                    A.insert(idx, idx + cols) = -1.0;
//                    A.insert(idx, idx + 1) = -2.0;
//                    b(idx) = 0.0;
//                    continue;
//                }
//
//                if (i + 1 > rows - 1) { //3
//                    if (j - 1 < 0) { //7
//                        A.insert(idx, idx - cols) = -2.0;
//                        A.insert(idx, idx + 1) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    if (j + 1 > cols - 1) { //6
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx - cols) = -2.0;
//                        b(idx) = 0.0;
//                        continue;
//                    }
//                    A.insert(idx, idx - cols) = -2.0;
//                    A.insert(idx, idx - 1) = -1.0;
//                    A.insert(idx, idx + 1) = -1.0;
//                    b(idx) = 0.0;
//                    continue;
//                }
//
//                A.insert(idx, idx + 1) = -1.0;
//                A.insert(idx, idx - 1) = -1.0;
//                A.insert(idx, idx + cols) = -1.0;
//                A.insert(idx, idx - cols) = -1.0;
//                b(idx) = 0.0;
//            }
//        }
//    }
//
//    A.makeCompressed();
//
//    double tol = 1e-4;
//    int maxIter = 10000;
//
//    x = VectorXd::Zero(total_size);
//
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            int idx = i * cols + j;
//            if (matrix[i][j] != 0) {
//                x(idx) = dtmStart[i][j];
//            }
//        }
//    }
//
//    for (int k = 0; k < maxIter; ++k) {
//        cout << "iter " << k << endl;
//        x_old = x;
//
//        for (int i = 0; i < total_size; ++i) {
//            double diag = A.coeff(i, i);
//            double sigma = 0.0;
//
//            for (int j = 0; j < total_size; ++j) {
//                if (j == i) continue;
//                sigma += A.coeff(i, j) * x(j);
//            }
//
//            x(i) = (b(i) - sigma) / diag;
//
//            int ii = i / cols;
//            int jj = i % cols;
//
//            if (x(i) > dtmStart[ii][jj]) {
//                x(i) = dtmStart[ii][jj];
//            }
//        }
//
//        if (k == 0 || k % 100 == 0) {
//            vector<vector<double>> laplaceSolution(rows, vector<double>(cols));
//            for (int i = 0; i < rows; ++i) {
//                for (int j = 0; j < cols; ++j) {
//                    laplaceSolution[i][j] = x(i * cols + j);
//                }
//            }
//
//            //saveMatrixToPGM(laplaceSolution, "SeptZacatPodmienkLaplaceSolutionInputTifMinHores1515.pgm");
//            saveTXTFor3D(laplaceSolution, 300, 1.0, k);
//        }
//
//        if ((x - x_old).norm() < tol) {
//            cout << "Gauss-Seidel converged in " << k + 1 << " iterations." << endl;
//            return x;
//        }
//    }
//
//    cout << "Gauss-Seidel reached maxIter." << endl;
//    return x;
//}
VectorXd solveSchemeGS(vector<vector<double>> matrix, vector<vector<double>> dtmStart, vector<vector<double>> sorLaplace, int r, int c, double omegaS) {
    int rows = r;
    int cols = c;
    int total_size = rows * cols;

    cout << rows << " " << cols << endl;
    cout << matrix.size() << " " << matrix[0].size() << endl;
    cout << dtmStart.size() << " " << dtmStart[0].size() << endl;

    VectorXd b(r * c), x(r * c), x_old(r * c);

    double tol = 1e-5;
    int maxIter = 1000000;

    double omega = omegaS;

    double h = 1.0;
    double L2Norm = 0.0;
    double tL2;
    double L2Norm0;
    int k = 0;

    // Формируем b так же по той же логике, как раньше в матричной схеме
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int idx = i * cols + j;

            if (matrix[i][j] != 0) {
                b(idx) = dtmStart[i][j];
            }
            else {
                b(idx) = 0.0;
            }
        }
    }

    x = VectorXd::Zero(total_size);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int idx = i * cols + j;
            /*if (matrix[i][j] != 0) {
                x(idx) = dtmStart[i][j];
            }*/
            //x(idx) = dtmStart[i][j];
            x(idx) = sorLaplace[i][j];
        }
    }

    for (k = 0; k < maxIter; ++k) {
        //cout << "iter " << k << endl;
        x_old = x;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int idx = i * cols + j;

                if (matrix[i][j] != 0) {
                    x(idx) = dtmStart[i][j];
                    continue;
                }
                else {
                    double diag = 4.0;
                    double sigma = 0.0;

                    if (j + 1 > cols - 1) { //2
                        if (i - 1 < 0) { //5
                            sigma += -2.0 * x(idx - 1);
                            sigma += -2.0 * x(idx + cols);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }
                            x(idx) = newValue;
                            continue;
                        }

                        if (i + 1 > rows - 1) { //6
                            sigma += -2.0 * x(idx - 1);
                            sigma += -2.0 * x(idx - cols);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }
                            x(idx) = newValue;
                            continue;
                        }

                        sigma += -2.0 * x(idx - 1);
                        sigma += -1.0 * x(idx + cols);
                        sigma += -1.0 * x(idx - cols);

                        double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                        if (newValue > dtmStart[i][j]) {
                            newValue = dtmStart[i][j];
                        }
                        x(idx) = newValue;
                        continue;
                    }

                    if (i - 1 < 0) { // 1
                        if (j + 1 > cols - 1) { // 5
                            sigma += -2.0 * x(idx - 1);
                            sigma += -2.0 * x(idx + cols);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }
                            x(idx) = newValue;
                            continue;
                        }

                        if (j - 1 < 0) { //8
                            sigma += -2.0 * x(idx + 1);
                            sigma += -2.0 * x(idx + cols);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }
                            x(idx) = newValue;
                            continue;
                        }

                        sigma += -1.0 * x(idx - 1);
                        sigma += -2.0 * x(idx + cols);
                        sigma += -1.0 * x(idx + 1);

                        double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                        if (newValue > dtmStart[i][j]) {
                            newValue = dtmStart[i][j];
                        }
                        x(idx) = newValue;
                        continue;
                    }

                    if (j - 1 < 0) { //4
                        if (i - 1 < 0) { //8
                            sigma += -2.0 * x(idx + 1);
                            sigma += -2.0 * x(idx + cols);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }
                            x(idx) = newValue;
                            continue;
                        }

                        if (i + 1 > rows - 1) { //7
                            sigma += -2.0 * x(idx - cols);
                            sigma += -2.0 * x(idx + 1);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }
                            x(idx) = newValue;
                            continue;
                        }

                        sigma += -1.0 * x(idx - cols);
                        sigma += -1.0 * x(idx + cols);
                        sigma += -2.0 * x(idx + 1);

                        double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                        if (newValue > dtmStart[i][j]) {
                            newValue = dtmStart[i][j];
                        }
                        x(idx) = newValue;
                        continue;
                    }

                    if (i + 1 > rows - 1) { // 3
                        if (j - 1 < 0) { // 7
                            sigma += -2.0 * x(idx - cols);
                            sigma += -2.0 * x(idx + 1);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }
                            x(idx) = newValue;
                            continue;
                        }

                        if (j + 1 > cols - 1) { //6
                            sigma += -2.0 * x(idx - 1);
                            sigma += -2.0 * x(idx - cols);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }
                            x(idx) = newValue;
                            continue;
                        }

                        sigma += -2.0 * x(idx - cols);
                        sigma += -1.0 * x(idx - 1);
                        sigma += -1.0 * x(idx + 1);

                        double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                        if (newValue > dtmStart[i][j]) {
                            newValue = dtmStart[i][j];
                        }
                        x(idx) = newValue;
                        continue;
                    }

                    sigma += -1.0 * x(idx + 1);     //i,j+1
                    sigma += -1.0 * x(idx - 1);     //i,j-1
                    sigma += -1.0 * x(idx + cols);  //i+1,j
                    sigma += -1.0 * x(idx - cols);  //i-1,j

                    double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                    if (newValue > dtmStart[i][j]) {
                        newValue = dtmStart[i][j];
                    }
                    x(idx) = newValue;
                }
            }
        }

        /*if(k == 0){
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    int index = i * cols + j;
                    L2Norm0 += h * h * pow(x_old[index] - x[index], 2);
                }
            }

            tL2 = sqrt(L2Norm0);
            L2Norm0 = tL2;

            cout << "L2 Norm 0: " << L2Norm0 << endl;
        }*/

        L2Norm = 0.0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int index = i * cols + j;
                L2Norm += h * h * pow(x_old[index] - x[index], 2);
            }
        }

        tL2 = sqrt(L2Norm);
        L2Norm = tL2;

        //cout << "L2 Norm: " << L2Norm << endl;

        /*if (k == 0 || k == 1 || k == 2 || (k < 1000 && k % 100 == 0) || k % 5000 == 0) {
            cout << "iter " << k << endl;
            cout << "L2 Norm: " << L2Norm << endl;
            vector<vector<double>> laplaceSolution(rows, vector<double>(cols));
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    laplaceSolution[i][j] = x(i * cols + j);
                }
            }

            double delta = 0.01;

            saveTXTFor3D(laplaceSolution, rows, 1.0, k);
            vector<vector<double>> underSurfaceWaterl(rows, vector<double>(cols));
            vector<vector<double>> onSurfaceWaterl(rows, vector<double>(cols));
            for (int j = 0; j < rows; ++j) {
                for (int k = 0; k < cols; ++k) {
                    if (laplaceSolution[j][k] < dtmStart[j][k] - delta)
                        underSurfaceWaterl[j][k] = 1;
                    else
                        underSurfaceWaterl[j][k] = 0;

                    if (laplaceSolution[j][k] >= dtmStart[j][k] - delta)
                        onSurfaceWaterl[j][k] = 1;
                    else
                        onSurfaceWaterl[j][k] = 0;
                }
            }
            saveMatrixToPGM(underSurfaceWaterl, "underSurfaceWaterTifAvgPSOR2Iter" + std::to_string(k + 1) + ".pgm");
            saveMatrixToPGM(onSurfaceWaterl, "onSurfaceWaterTifAvgPSOR2Iter" + std::to_string(k + 1) + ".pgm");

            vector<vector<double>> difCurrentLap(rows, vector<double>(cols));

            difCurrentLap = compareValuesV2(laplaceSolution, dtmStart, 0.1);
            saveMatrixToPGM(difCurrentLap, "diff01WaterTifAvgHoresIterPSOR2FebNoEraseIter" + std::to_string(k + 1) + ".pgm");
            difCurrentLap = compareValuesV2(laplaceSolution, dtmStart, 0.2);
            saveMatrixToPGM(difCurrentLap, "diff02WaterTifAvgHoresIterPSOR2FebNoEraseIter" + std::to_string(k + 1) + ".pgm");
            difCurrentLap = compareValuesV2(laplaceSolution, dtmStart, 0.3);
            saveMatrixToPGM(difCurrentLap, "diff03WaterTifAvgHoresIterPSOR2FebNoEraseIter" + std::to_string(k + 1) + ".pgm");
            difCurrentLap = compareValuesV2(laplaceSolution, dtmStart, 0.5);
            saveMatrixToPGM(difCurrentLap, "diff05WaterTifAvgHoresIterPSOR2FebNoEraseIter" + std::to_string(k + 1) + ".pgm");
            difCurrentLap = compareValuesV2(laplaceSolution, dtmStart, 0.7);
            saveMatrixToPGM(difCurrentLap, "diff07WaterTifAvgHoresIterPSOR2FebNoEraseIter" + std::to_string(k + 1) + ".pgm");
            difCurrentLap = compareValuesV2(laplaceSolution, dtmStart, 1.0);
            saveMatrixToPGM(difCurrentLap, "diff10WaterTifAvgHoresIterPSOR2FebNoEraseIter" + std::to_string(k + 1) + ".pgm");

            saveMatrixToPGM(laplaceSolution, "SeptZacatPodmienkLaplaceSolutionInputTifPSOR2Iter" + std::to_string(k + 1) + ".pgm");
        }*/

        /*if ((x - x_old).norm() < tol) {
            cout << "SOR converged in " << k + 1 << " iterations." << endl;
            return x;
        }*/

        if (L2Norm < tol) {
            cout << "PSOR converged in " << k + 1 << " iterations." << endl;
            cout << "iter " << k << endl;
            cout << "L2 Norm: " << L2Norm << endl;
            break;
        }

    }

    cout << "iter " << k << endl;
    cout << "L2 Norm: " << L2Norm << endl;
    //cout << "PSOR reached maxIter." << endl;
    return x;
}

VectorXd solveSchemeSORLaplace(vector<vector<double>> matrix, vector<vector<double>> dtmStart, int r, int c) {
    int rows = r;
    int cols = c;
    int total_size = rows * cols;

    cout << rows << " " << cols << endl;
    cout << matrix.size() << " " << matrix[0].size() << endl;
    cout << dtmStart.size() << " " << dtmStart[0].size() << endl;

    VectorXd b(r * c), x(r * c), x_old(r * c);

    double tol = 1e-3;
    int maxIter = 1000000;

    double omega = 1.9;

    double h = 1.0;
    double L2Norm = 0.0;
    double tL2;
    double L2Norm0;

    // Формируем b так же по той же логике, как раньше в матричной схеме
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int idx = i * cols + j;

            if (matrix[i][j] != 0) {
                b(idx) = dtmStart[i][j];
            }
            else {
                b(idx) = 0.0;
            }
        }
    }

    x = VectorXd::Zero(total_size);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int idx = i * cols + j;
            /*if (matrix[i][j] != 0) {
                x(idx) = dtmStart[i][j];
            }*/
            //x(idx) = dtmStart[i][j];
            x(idx) = 0;
        }
    }

    for (int k = 0; k < maxIter; ++k) {
        //cout << "iter " << k << endl;
        x_old = x;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int idx = i * cols + j;

                if (matrix[i][j] != 0) {
                    x(idx) = dtmStart[i][j];
                    continue;
                }
                else {
                    double diag = 4.0;
                    double sigma = 0.0;

                    if (j + 1 > cols - 1) { //2
                        if (i - 1 < 0) { //5
                            sigma += -2.0 * x(idx - 1);
                            sigma += -2.0 * x(idx + cols);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            /*if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }*/
                            x(idx) = newValue;
                            continue;
                        }

                        if (i + 1 > rows - 1) { //6
                            sigma += -2.0 * x(idx - 1);
                            sigma += -2.0 * x(idx - cols);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            /*if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }*/
                            x(idx) = newValue;
                            continue;
                        }

                        sigma += -2.0 * x(idx - 1);
                        sigma += -1.0 * x(idx + cols);
                        sigma += -1.0 * x(idx - cols);

                        double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                        /*if (newValue > dtmStart[i][j]) {
                            newValue = dtmStart[i][j];
                        }*/
                        x(idx) = newValue;
                        continue;
                    }

                    if (i - 1 < 0) { // 1
                        if (j + 1 > cols - 1) { // 5
                            sigma += -2.0 * x(idx - 1);
                            sigma += -2.0 * x(idx + cols);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            /*if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }*/
                            x(idx) = newValue;
                            continue;
                        }

                        if (j - 1 < 0) { //8
                            sigma += -2.0 * x(idx + 1);
                            sigma += -2.0 * x(idx + cols);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            /*if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }*/
                            x(idx) = newValue;
                            continue;
                        }

                        sigma += -1.0 * x(idx - 1);
                        sigma += -2.0 * x(idx + cols);
                        sigma += -1.0 * x(idx + 1);

                        double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                        /*if (newValue > dtmStart[i][j]) {
                            newValue = dtmStart[i][j];
                        }*/
                        x(idx) = newValue;
                        continue;
                    }

                    if (j - 1 < 0) { //4
                        if (i - 1 < 0) { //8
                            sigma += -2.0 * x(idx + 1);
                            sigma += -2.0 * x(idx + cols);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            /*if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }*/
                            x(idx) = newValue;
                            continue;
                        }

                        if (i + 1 > rows - 1) { //7
                            sigma += -2.0 * x(idx - cols);
                            sigma += -2.0 * x(idx + 1);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            /*if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }*/
                            x(idx) = newValue;
                            continue;
                        }

                        sigma += -1.0 * x(idx - cols);
                        sigma += -1.0 * x(idx + cols);
                        sigma += -2.0 * x(idx + 1);

                        double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                        /*if (newValue > dtmStart[i][j]) {
                            newValue = dtmStart[i][j];
                        }*/
                        x(idx) = newValue;
                        continue;
                    }

                    if (i + 1 > rows - 1) { // 3
                        if (j - 1 < 0) { // 7
                            sigma += -2.0 * x(idx - cols);
                            sigma += -2.0 * x(idx + 1);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            /*if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }*/
                            x(idx) = newValue;
                            continue;
                        }

                        if (j + 1 > cols - 1) { //6
                            sigma += -2.0 * x(idx - 1);
                            sigma += -2.0 * x(idx - cols);

                            double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                            /*if (newValue > dtmStart[i][j]) {
                                newValue = dtmStart[i][j];
                            }*/
                            x(idx) = newValue;
                            continue;
                        }

                        sigma += -2.0 * x(idx - cols);
                        sigma += -1.0 * x(idx - 1);
                        sigma += -1.0 * x(idx + 1);

                        double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                        /*if (newValue > dtmStart[i][j]) {
                            newValue = dtmStart[i][j];
                        }*/
                        x(idx) = newValue;
                        continue;
                    }

                    sigma += -1.0 * x(idx + 1);     //i,j+1
                    sigma += -1.0 * x(idx - 1);     //i,j-1
                    sigma += -1.0 * x(idx + cols);  //i+1,j
                    sigma += -1.0 * x(idx - cols);  //i-1,j

                    double newValue = ((omega * (b(idx) - sigma)) / diag) + (1 - omega) * x(idx);
                    /*if (newValue > dtmStart[i][j]) {
                        newValue = dtmStart[i][j];
                    }*/
                    x(idx) = newValue;
                }
            }
        }

        /*if(k == 0){
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    int index = i * cols + j;
                    L2Norm0 += h * h * pow(x_old[index] - x[index], 2);
                }
            }

            tL2 = sqrt(L2Norm0);
            L2Norm0 = tL2;

            cout << "L2 Norm 0: " << L2Norm0 << endl;
        }*/

        L2Norm = 0.0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int index = i * cols + j;
                L2Norm += h * h * pow(x_old[index] - x[index], 2);
            }
        }

        tL2 = sqrt(L2Norm);
        L2Norm = tL2;

        //cout << "L2 Norm: " << L2Norm << endl;

        if (k == 0 || k < 10 || k % 1000 == 0) {
            cout << "iter " << k << endl;
            cout << "L2 Norm: " << L2Norm << endl;
            /*vector<vector<double>> laplaceSolution(rows, vector<double>(cols));
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    laplaceSolution[i][j] = x(i * cols + j);
                }
            }

            double delta = 0.01;

            saveTXTFor3D(laplaceSolution, rows, 1.0, k);*/
            /*vector<vector<double>> underSurfaceWaterl(rows, vector<double>(cols));
            vector<vector<double>> onSurfaceWaterl(rows, vector<double>(cols));
            for (int j = 0; j < rows; ++j) {
                for (int k = 0; k < cols; ++k) {
                    if (laplaceSolution[j][k] < dtmStart[j][k] - delta)
                        underSurfaceWaterl[j][k] = 1;
                    else
                        underSurfaceWaterl[j][k] = 0;

                    if (laplaceSolution[j][k] >= dtmStart[j][k] - delta)
                        onSurfaceWaterl[j][k] = 1;
                    else
                        onSurfaceWaterl[j][k] = 0;
                }
            }
            saveMatrixToPGM(underSurfaceWaterl, "underSurfaceWaterTifAvgSORIter" + std::to_string(k + 1) + ".pgm");
            saveMatrixToPGM(onSurfaceWaterl, "onSurfaceWaterTifAvgSORIter" + std::to_string(k + 1) + ".pgm");

            vector<vector<double>> difCurrentLap(rows, vector<double>(cols));

            difCurrentLap = compareValuesV2(laplaceSolution, dtmStart, 0.1);
            saveMatrixToPGM(difCurrentLap, "diff01WaterTifAvgHoresIterSORFebNoEraseIter" + std::to_string(k + 1) + ".pgm");
            difCurrentLap = compareValuesV2(laplaceSolution, dtmStart, 0.2);
            saveMatrixToPGM(difCurrentLap, "diff02WaterTifAvgHoresIterSORFebNoEraseIter" + std::to_string(k + 1) + ".pgm");
            difCurrentLap = compareValuesV2(laplaceSolution, dtmStart, 0.3);
            saveMatrixToPGM(difCurrentLap, "diff03WaterTifAvgHoresIterSORFebNoEraseIter" + std::to_string(k + 1) + ".pgm");
            difCurrentLap = compareValuesV2(laplaceSolution, dtmStart, 0.5);
            saveMatrixToPGM(difCurrentLap, "diff05WaterTifAvgHoresIterSORFebNoEraseIter" + std::to_string(k + 1) + ".pgm");
            difCurrentLap = compareValuesV2(laplaceSolution, dtmStart, 0.7);
            saveMatrixToPGM(difCurrentLap, "diff07WaterTifAvgHoresIterSORFebNoEraseIter" + std::to_string(k + 1) + ".pgm");
            difCurrentLap = compareValuesV2(laplaceSolution, dtmStart, 1.0);
            saveMatrixToPGM(difCurrentLap, "diff10WaterTifAvgHoresIterSORFebNoEraseIter" + std::to_string(k + 1) + ".pgm");

            saveMatrixToPGM(laplaceSolution, "SeptZacatPodmienkLaplaceSolutionInputTifSORIter" + std::to_string(k + 1) + ".pgm");*/
        }

        /*if ((x - x_old).norm() < tol) {
            cout << "SOR converged in " << k + 1 << " iterations." << endl;
            return x;
        }*/

        if (L2Norm < tol) {
            cout << "SOR reached tolerance on iter " << k + 1 << endl;
            break;
        }

    }

    cout << "SOR reached maxIter." << endl;
    return x;
}

VectorXd solveScheme(vector<vector<double>> matrix, vector<vector<double>> matrixInPrevTime, int n, double tau = 10, double h = 1) {
    int rows = n;
    int cols = n;
    int total_size = rows * cols;

    SparseMatrix<double> A(n * n, n * n);
    SparseMatrix<double> temp(n * n, n * n);
    VectorXd b(n * n), x(n * n);

    A.reserve(Eigen::VectorXi::Constant(n * n, 5));


    double c = tau / pow(h, 2);

    //cout << c << endl;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int idx = i * cols + j;
            if (matrix[i][j] != 0) {
                A.insert(idx, idx) = 1.0;
                b(idx) = matrix[i][j];
            }
            else {
                A.insert(idx, idx) = 1.0 + 4 * c;
                if (j + 1 > cols - 1) { //2
                    if (i - 1 < 0) { //5
                        A.insert(idx, idx - 1) = -2.0 * c;
                        A.insert(idx, idx + cols) = -2.0 * c;
                        b(idx) = matrixInPrevTime[i][j];
                        //b(idx) = 0;
                        continue;
                    }
                    if (i + 1 > rows - 1) { //6
                        A.insert(idx, idx - 1) = -2.0 * c;
                        A.insert(idx, idx - cols) = -2.0 * c;
                        b(idx) = matrixInPrevTime[i][j];
                        //b(idx) = 0;
                        continue;
                    }
                    A.insert(idx, idx - 1) = -2.0 * c;
                    A.insert(idx, idx + cols) = -1.0 * c;
                    A.insert(idx, idx - cols) = -1.0 * c;
                    b(idx) = matrixInPrevTime[i][j];
                    //b(idx) = 0;
                    continue;
                }
                if (i - 1 < 0) { // 1
                    if (j + 1 > cols - 1) { // 5
                        A.insert(idx, idx - 1) = -2.0 * c;
                        A.insert(idx, idx + cols) = -2.0 * c;
                        b(idx) = matrixInPrevTime[i][j];
                        //b(idx) = 0;
                        continue;
                    }
                    if (j - 1 < 0) { //8
                        A.insert(idx, idx + 1) = -2.0 * c;
                        A.insert(idx, idx + cols) = -2.0 * c;
                        b(idx) = matrixInPrevTime[i][j];
                        //b(idx) = 0;
                        continue;
                    }
                    A.insert(idx, idx - 1) = -1.0 * c;
                    A.insert(idx, idx + cols) = -2.0 * c;
                    A.insert(idx, idx + 1) = -1.0 * c;
                    b(idx) = matrixInPrevTime[i][j];
                    //b(idx) = 0;
                    continue;
                }
                if (j - 1 < 0) { //4
                    if (i - 1 < 0) { //8
                        A.insert(idx, idx + 1) = -2.0 * c;
                        A.insert(idx, idx + cols) = -2.0 * c;
                        b(idx) = matrixInPrevTime[i][j];
                        //b(idx) = 0;
                        continue;
                    }
                    if (i + 1 > rows - 1) { //7
                        A.insert(idx, idx - cols) = -2.0 * c;
                        A.insert(idx, idx + 1) = -2.0 * c;
                        b(idx) = matrixInPrevTime[i][j];
                        //b(idx) = 0;
                        continue;
                    }
                    A.insert(idx, idx - cols) = -1.0 * c;
                    A.insert(idx, idx + cols) = -1.0 * c;
                    A.insert(idx, idx + 1) = -2.0 * c;
                    b(idx) = matrixInPrevTime[i][j];
                    //b(idx) = 0;
                    continue;
                }
                if (i + 1 > rows - 1) { // 3
                    if (j - 1 < 0) { // 7
                        A.insert(idx, idx - cols) = -2.0 * c;
                        A.insert(idx, idx + 1) = -2.0 * c;
                        b(idx) = matrixInPrevTime[i][j];
                        //b(idx) = 0;
                        continue;
                    }
                    if (j + 1 > cols - 1) { //6
                        A.insert(idx, idx - 1) = -2.0 * c;
                        A.insert(idx, idx - cols) = -2.0 * c;
                        b(idx) = matrixInPrevTime[i][j];
                        //b(idx) = 0;
                        continue;
                    }
                    A.insert(idx, idx - cols) = -2.0 * c;
                    A.insert(idx, idx - 1) = -1.0 * c;
                    A.insert(idx, idx + 1) = -1.0 * c;
                    b(idx) = matrixInPrevTime[i][j];
                    //b(idx) = 0;
                    continue;
                }
                A.insert(idx, idx + 1) = -1.0 * c;//i,j+1
                A.insert(idx, idx - 1) = -1.0 * c;//i,j-1
                A.insert(idx, idx + cols) = -1.0 * c;//i+1,j
                A.insert(idx, idx - cols) = -1.0 * c;//i-1,j
                b(idx) = matrixInPrevTime[i][j];
                //b(idx) = 0;
            }
        }
    }

    temp = A;
    A.makeCompressed();
    BiCGSTAB<SparseMatrix<double>> solver;
    solver.compute(A);
    x = solver.solve(b);

    return x;
}

vector<vector<double>> cutCenter500x500(const vector<vector<double>>& matrix) {
    int rows = static_cast<int>(matrix.size());
    if (rows == 0) return {};

    int cols = static_cast<int>(matrix[0].size());

    const int subRows = 500;
    const int subCols = 500;

    // top-left corner of the cutted img
    int startRow = (rows - subRows - 300) / 2;
    int startCol = (cols - subCols - 400) / 2;

    vector<vector<double>> sub(subRows, vector<double>(subCols));

    for (int i = 0; i < subRows; ++i) {
        for (int j = 0; j < subCols; ++j) {
            sub[i][j] = matrix[startRow + i][startCol + j];
        }
    }

    return sub;
}



double f(double x, double y) {
    return sin(x) * sin(y);
}

int main() {

    double a = 1;

    int n = 2001;
    int rowsTifFull = 2001;
    int colsTifFull = 2001;
    int rowsTifMin = 2001;
    int colsTifMin = 2001;
    int rows = n;
    int cols = n;
    int total_size = rows * cols;

    vector<vector<double>> matrix(rows, vector<double>(cols));
    //double h = (a - 0.0) / (double)(500 - 1);

    double h = 1.0;
    //double h = 1;
    //int x1 = 5, y1_1 = 5, y1_2 = 20; // Начало прямых
    //int x2 = 25, y2_1 = 5, y2_2 = 20; // Конец прямых
    //// Узловые точки первой прямой
    //std::vector<std::pair<int, int>> line1 = bresenhamLine(x1, y1_1, x1, y1_2);

    // Узловые точки второй прямой
   // std::vector<std::pair<int, int>> line2 = bresenhamLine(x2, y2_1, x2, y2_2);


    //std::ofstream file("lines.txt");
    //if (!file.is_open()) {
    //    std::cerr << "Error opening file for writing!" << std::endl;
    //    return 1;
    //}

    //file << "(* First Line *)\n";
    //file << "line1 = {";
    //for (size_t i = 0; i < line1.size(); ++i) {
    //    file << "{" << line1[i].first << ", " << line1[i].second << "}";
    //    if (i != line1.size() - 1) file << ", ";
    //}
    //file << "};\n";

    // Записываем точки второй прямой в файл
    /*file << "(* Second Line *)\n";
    file << "line2 = {";
    for (size_t i = 0; i < line2.size(); ++i) {
        file << "{" << line2[i].first << ", " << line2[i].second << "}";
        if (i != line2.size() - 1) file << ", ";
    }
    file << "};\n";*/

    // Добавляем команду для построения графика в Wolfram Mathematica
    //file << "\nListPlot[{line1, line2}, PlotStyle -> {Red, Blue}, "
    //    << "Joined -> True, AspectRatio -> Automatic, "
    //    << "AxesLabel -> {\"x\", \"y\"}, PlotMarkers -> Automatic];\n";

    //// Закрываем файл
    //file.close();



    vector<vector<double>> inputMatrix;
    //string filename = "inputForSolveMembr2.txt";  // Specify your input file name here 
    //string filename = "inputForSolveMembrTestObr21AfterEraseV2Ostacle1V2.txt";
    string filename = "inputForSolveMembrTestObr21AfterEraseV2.txt";
    //string filename = "inputForSolveMembrIter1Sept.txt";



    matrix = loadMatrixFromFile(filename);

    //saveMatrixToPGM(matrix, "inputMatrixIter0.pgm");

    filename = "Hores_square_DTM_data.pgm";

    //vector<vector<double>> downloadedMatrixData = readPGMToMatrix(filename);

    //saveTXTFor3D(downloadedMatrixData, n, h, -1);

    filename = "solutionWaters50TestObr21AfterEraseV2ForCompareObst1V2.txt";

    vector<vector<double>> laplaceSolution1 = loadMatrixFromFile(filename);

    //new tif 500 part start

//filename = "Latorica_ZBGISVodstvo2.tif";

//auto mask = readTIFFToBinaryMatrix("ZBGIS_Vodstvo_Hores.tif");

    vector<vector<double>> downloadedMatrixDataTif = readTIFFToMatrix("dmr5_jtsk03_10m_avg_Hores_clip_from_final.tif");

    /*vector<vector<double>> inputTif(rowsTifFull, vector<double>(colsTifFull));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            inputTif[i][j] = (double)mask[i][j];
        }
    }*/

    //start dif
//   rows = 1875;
//   cols = 1875;

//   /*vector<vector<double>> sor = readPGMToMatrix("SeptZacatPodmienkLaplaceSolutionInputTifSOR.pgm");
//   vector<vector<double>> cas = readPGMToMatrix("SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresNoEraseFeb10e-4Iter1120.pgm");*/

//   vector<vector<double>> sor = readPGMToMatrix("onSurfaceWaterTifAvgSOR.pgm");
//   vector<vector<double>> cas = readPGMToMatrix("onSurfaceWaterTifAvgHoresIterNoEraseFeb1103.pgm");


//   double L2Norm000 = 0;

//   for (int i = 0; i < rows; i++) {
//       for (int j = 0; j < cols; j++) {
//           int index = i * cols + j;
//           L2Norm000 += h * h * pow(sor[i][j] - cas[i][j], 2);

//           /*if(sor[i][j] != cas[i][j])
//               L2Norm000++;*/
//       }
//   }

//   double tL22 = sqrt(L2Norm000);
//   L2Norm000 = tL22;

//   cout << L2Norm000 << endl;

//   return 0;

   //cout << "Dif between onSurface SOR and CAS: " << L2Norm000 << " " << 1875*1875 << " " << L2Norm000/(1875*1875) << endl;

//   sor = readPGMToMatrix("diff01WaterTifAvgHoresIterSORFebNoErase.pgm");
//   cas = readPGMToMatrix("diff01SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresNoEraseFeb10e-4Iter1120.pgm");
//   
//   L2Norm000 = 0;

//   for (int i = 0; i < rows; i++) {
//       for (int j = 0; j < cols; j++) {
//           /*int index = i * cols + j;
//           L2Norm000 += h * h * pow(sor[i][j] - cas[i][j], 2);*/

//           if (sor[i][j] != cas[i][j])
//               L2Norm000++;
//       }
//   }

//   //double tL22 = sqrt(L2Norm000);
//   //L2Norm000 = tL22;

//   cout << "Dif between 01 SOR and CAS: " << L2Norm000 << " " << 1875 * 1875 << " " << L2Norm000 / (1875 * 1875) << endl;

//   sor = readPGMToMatrix("diff02WaterTifAvgHoresIterSORFebNoErase.pgm");
//   cas = readPGMToMatrix("diff02SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresNoEraseFeb10e-4Iter1120.pgm");

//   L2Norm000 = 0;

//   for (int i = 0; i < rows; i++) {
//       for (int j = 0; j < cols; j++) {
//           /*int index = i * cols + j;
//           L2Norm000 += h * h * pow(sor[i][j] - cas[i][j], 2);*/

//           if (sor[i][j] != cas[i][j])
//               L2Norm000++;
//       }
//   }

//   //double tL22 = sqrt(L2Norm000);
//   //L2Norm000 = tL22;

//   cout << "Dif between 02 SOR and CAS: " << L2Norm000 << " " << 1875 * 1875 << " " << L2Norm000 / (1875 * 1875) << endl;

//   sor = readPGMToMatrix("diff03WaterTifAvgHoresIterSORFebNoErase.pgm");
//   cas = readPGMToMatrix("diff03SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresNoEraseFeb10e-4Iter1120.pgm");

//   L2Norm000 = 0;

//   for (int i = 0; i < rows; i++) {
//       for (int j = 0; j < cols; j++) {
//           /*int index = i * cols + j;
//           L2Norm000 += h * h * pow(sor[i][j] - cas[i][j], 2);*/

//           if (sor[i][j] != cas[i][j])
//               L2Norm000++;
//       }
//   }

//   //double tL22 = sqrt(L2Norm000);
//   //L2Norm000 = tL22;

//   cout << "Dif between 03 SOR and CAS: " << L2Norm000 << " " << 1875 * 1875 << " " << L2Norm000 / (1875 * 1875) << endl;


//   
//   return 0;
                                                                                                                                                                                                                       //end dif

   //saveMatrixToPGM(inputTif, "ZBGIS_Vodstvo_Hores.pgm");
   //saveMatrixToPGM(downloadedMatrixDataTif, "dmr5_jtsk03_10m_avg_Hores_clip_from_final.pgm");
   //saveMatrixToFile(downloadedMatrixDataTif, "data_DTM3_from_tif_data.txt");
   //saveMatrixToFile(inputTif, "ZBGIS_Vodstvo_Hores.txt");

   /*vector<vector<double>> downloadedMatrixDataTif500 = cutCenter500x500(downloadedMatrixDataTif);
   vector<vector<double>> inputTif500 = cutCenter500x500(inputTif);

   saveTXTFor3D(downloadedMatrixDataTif500, 500, h, -1);

   //saveMatrixToPGM(inputTif500, "inputMatrixTif500.pgm");
   //saveMatrixToPGM(downloadedMatrixDataTif500, "data_DTM3_from_tif_500.pgm");
   //saveMatrixToFile(downloadedMatrixDataTif500, "data_DTM3_from_tif_data_500.txt");

   cout << downloadedMatrixDataTif500.size() << " " << downloadedMatrixDataTif500[0].size() << endl;
   cout << inputTif500.size() << " " << inputTif500[0].size() << endl;

   rows = rowsTifMin;
   cols = colsTifMin;
   n = 500;
   double delta = 0.01;
   matrix.resize(rows, vector<double>(cols));
   matrix = inputTif500;
   cout << matrix.size() << " " << matrix[0].size() << endl;

   for (int i = 0; i < rows; i++) {
       for (int j = 0; j < cols; j++) {
           if(matrix[i][j] != 0)
               matrix[i][j] = downloadedMatrixDataTif500[i][j];
       }
   }

   VectorXd xLap(n * n);

   xLap = solveSchemeLaplace(matrix, downloadedMatrixDataTif500, 500, 500);

   vector<vector<double>> laplaceSolution(rows, vector<double>(cols));
   for (int i = 0; i < rows; ++i) {
       for (int j = 0; j < cols; ++j) {
           laplaceSolution[i][j] = xLap(i * cols + j);
       }
   }

   saveMatrixToPGM(laplaceSolution, "SeptZacatPodmienkLaplaceSolutionInputTif500.pgm");
   */
   //new tif 500 part end

   //new tif hores start
//filename = "Latorica_ZBGISVodstvo2.tif";

//auto mask = readTIFFToBinaryMatrix("ZBGIS_Vodstvo_export_10m_Hores.tif", 2);

//vector<vector<double>> downloadedMatrixDataTif = readTIFFToMatrix("dmr5_jtsk03_10m_min_Hores.tif");
/*
vector<vector<double>> inputTif(2001, vector<double>(2001));

for (int i = 0; i < 2001; i++) {
    for (int j = 0; j < 2001; j++) {
        //cout << mask[i][j] << " ";
        inputTif[i][j] = (double)mask[i][j];
    }
    //cout << endl;
}
*/


//saveMatrixToPGM(inputTif, "inputMatrixTifHoresWithoutAnyChanges.pgm");
//saveMatrixToPGM(downloadedMatrixDataTif, "data_DTM5_from_tifHores.pgm");
//saveMatrixToFile(inputTif, "inputMatrixTifHoresWithoutAnyChanges.txt"); 

                                                                                                                                                                                                   //unkoment zacatok for SOR
//vector<vector<double>> inputTifFromFile = loadMatrixFromFile("ZBGIS_Vodstvo_Hores_v2_AfterErase.txt");
    vector<vector<double>> inputTifFromFile = loadMatrixFromFile("ZBGIS_Vodstvo_Hores_v2.txt");

    //vector<vector<double>> inputTifFromFileErase = readPGMToMatrix("ZBGIS_Vodstvo_Hores_v2.pgm");
    ///*for (int i = 0; i < 2001; i++) {
    //    for (int j = 0; j < 2001; j++) {
    //        if (inputTifFromFileErase[i][j] < 1.0)
    //            inputTifFromFileErase[i][j] = 0.0;
    //    }
    //}*/

    //for (int i = 0; i < 2001; i++) {
    //    for (int j = 0; j < 2001; j++) {
    //        if (inputTifFromFileErase[i][j] == 255.0)
    //            inputTifFromFileErase[i][j] = 1.0;
    //        else
    //            inputTifFromFileErase[i][j] = 0.0;
    //    }
    //}
    ////vector<vector<double>> inputTifFromFile = loadMatrixFromFile("inputForSolveMembr9AfterErase.txt");
    ///*for (int i = 0; i < 738; ++i) {
    //    for (int j = 0; j < 546; ++j) {
    //        inputTifFromFile[i][j] = 0;

    //    }
    //}*/

    //saveMatrixToPGM(inputTifFromFile, "ZBGIS_Vodstvo_Hores_v2_AfterErase.pgm");
    //saveMatrixToFile(inputTifFromFileErase, "ZBGIS_Vodstvo_Hores_v2_AfterErase.txt");


    rows = 1875;
    cols = 1875;
    vector<vector<double>> downloadedMatrixDataTif500(rows, vector<double>(cols));
    vector<vector<double>> inputTif500(rows, vector<double>(cols));

    for (int i = 0; i < 1875; i++) {
        for (int j = 0; j < 1875; j++) {
            downloadedMatrixDataTif500[i][j] = downloadedMatrixDataTif[i][j];
            inputTif500[i][j] = inputTifFromFile[i][j];
        }
    }

    /*saveTXTFor3D(downloadedMatrixDataTif, 1875, h, -1);
    saveMatrixToPGM(inputTif500, "ZBGIS_Vodstvo_Hores_NoErase_1875.pgm");
    saveMatrixToPGM(inputTif500, "inputMatrixTif500.pgm");
    saveMatrixToPGM(downloadedMatrixDataTif500, "dmr5_jtsk03_10m_avg_Hores_clip_from_final_1515.pgm");
    saveMatrixToFile(downloadedMatrixDataTif500, "inputMatrixTif500.txt");*/


    cout << downloadedMatrixDataTif500.size() << " " << downloadedMatrixDataTif500[0].size() << endl;
    cout << inputTif500.size() << " " << inputTif500[0].size() << endl;

    n = 1875;
    double delta = 0.01;
    matrix.resize(rows, vector<double>(cols));
    matrix = inputTif500;
    cout << matrix.size() << " " << matrix[0].size() << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0)
                matrix[i][j] = downloadedMatrixDataTif500[i][j];
        }
    }
    //unkoment konex for SOR
//test koment start
//VectorXd xLap(n * n);

////xLap = solveSchemeLaplace(matrix, downloadedMatrixDataTif500, 1875, 1875);
//xLap = solveSchemeGS(matrix, downloadedMatrixDataTif500, 1875, 1875);

//vector<vector<double>> laplaceSolution(rows, vector<double>(cols));
//for (int i = 0; i < rows; ++i) {
//    for (int j = 0; j < cols; ++j) {
//        laplaceSolution[i][j] = xLap(i * cols + j);
//    }
//}

//vector<vector<double>> underSurfaceWater2(rows, vector<double>(cols));
//vector<vector<double>> onSurfaceWater2(rows, vector<double>(cols));
//for (int j = 0; j < rows; ++j) {
//    for (int k = 0; k < cols; ++k) {
//        if (laplaceSolution[j][k] < downloadedMatrixDataTif500[j][k] - delta)
//            underSurfaceWater2[j][k] = 1;
//        else
//            underSurfaceWater2[j][k] = 0;

//        if (laplaceSolution[j][k] >= downloadedMatrixDataTif500[j][k] - delta)
//            onSurfaceWater2[j][k] = 1;
//        else
//            onSurfaceWater2[j][k] = 0;
//    }
//}
////saveMatrixToPGM(underSurfaceWater2, "underSurfaceWaterTifAvgHoresIterLaplaceFebAfterEraseV2.pgm");
//////saveMatrixToPGM(onSurfaceWater2, "onSurfaceWaterTifAvgHoresIterLaplaceFebNOErase.pgm");

////vector<vector<double>> difCurrentLap;

////difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.1);
////saveMatrixToPGM(difCurrentLap, "diff01WaterTifAvgHoresIterLaplaceFebAfterEraseV2.pgm");
////difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.2);
////saveMatrixToPGM(difCurrentLap, "diff02WaterTifAvgHoresIterLaplaceFebAfterEraseV2.pgm");
////difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.3);
////saveMatrixToPGM(difCurrentLap, "diff03WaterTifAvgHoresIterLaplaceFebAfterEraseV2.pgm");
////difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.5);
////saveMatrixToPGM(difCurrentLap, "diff05WaterTifAvgHoresIterLaplaceFebAfterEraseV2.pgm");
////difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.7);
////saveMatrixToPGM(difCurrentLap, "diff07WaterTifAvgHoresIterLaplaceFebAfterEraseV2.pgm");
////difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 1.0);
////saveMatrixToPGM(difCurrentLap, "diff10WaterTifAvgHoresIterLaplaceFebAfterEraseV2.pgm");

//saveMatrixToPGM(underSurfaceWater2, "underSurfaceWaterTifAvgHoresIterGaussSedlFebAfterEraseV2.pgm");
////saveMatrixToPGM(onSurfaceWater2, "onSurfaceWaterTifAvgHoresIterLaplaceFebNOErase.pgm");

//vector<vector<double>> difCurrentLap;

//difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.1);
//saveMatrixToPGM(difCurrentLap, "diff01WaterTifAvgHoresIterGaussSedlFebAfterEraseV2.pgm");
//difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.2);
//saveMatrixToPGM(difCurrentLap, "diff02WaterTifAvgHoresIterGaussSedlFebAfterEraseV2.pgm");
//difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.3);
//saveMatrixToPGM(difCurrentLap, "diff03WaterTifAvgHoresIterGaussSedlFebAfterEraseV2.pgm");
//difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.5);
//saveMatrixToPGM(difCurrentLap, "diff05WaterTifAvgHoresIterGaussSedlFebAfterEraseV2.pgm");
//difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.7);
//saveMatrixToPGM(difCurrentLap, "diff07WaterTifAvgHoresIterGaussSedlFebAfterEraseV2.pgm");
//difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 1.0);
//saveMatrixToPGM(difCurrentLap, "diff10WaterTifAvgHoresIterGaussSedlFebAfterEraseV2.pgm");
                                                                                                                                                                //test koment end

                                                                                                                                                                                                            //unkoment konec
//saveMatrixToPGM(laplaceSolution, "SeptZacatPodmienkLaplaceSolutionInputTifMinHores1515.pgm");
                               //new tif hores end 

                                                                                                                                                //new sin start 300 last
//   double lenX = 2 * 3.14;
//   double lenY = 2 * 3.14;
//   n = 300;
//   rows = 300;
//   cols = 300;
//   //int x1 = 5, y1_1 = 5, y1_2 = 20; // Начало прямых
//   //int x2 = 25, y2_1 = 5, y2_2 = 20; // Конец прямых
//   ////// Узловые точки первой прямой
//   //std::vector<std::pair<int, int>> line1 = bresenhamLine(x1, y1_1, x1, y1_2)
//   double delta = 0.01;
//   double hX = (lenX - 0.0) / (double)(n - 1);
//   double hY = (lenY - 0.0) / (double)(n - 1);
//   double xNow = 0;
//   double yNow = 0;
//   vector<vector<double>> downloadedMatrixDataTif500(rows, vector<double>(cols));
//   vector<vector<double>> inputTif500(rows, vector<double>(cols));
//   for (int i = 0; i < rows; ++i) {
//       for (int j = 0; j < cols; ++j) {
//           downloadedMatrixDataTif500[i][j] = f(xNow, yNow);
//           yNow += hY;
//       }
//       yNow = 0;
//       xNow += hX;
//   }
//   saveTXTFor3D(downloadedMatrixDataTif500, 300, h, -1);
//   //                                                                                                                                                
//   //                                                                                                                            //two parallel lines
//   /*
//   for (int i = 0; i < rows; i++) {
//       for (int j = 0; j < cols; j++) {
//           inputTif500[i][j] = 0;
//       }
//   }
//   yNow = 0;
//   for (int i = 0; i < rows; ++i) {
//       xNow = 3.14 / 2.0;
//       int j = 125;
//       inputTif500[j][i] = 1.0;
//   }
//   yNow = 0;
//   for (int i = 0; i < rows; ++i) {
//       xNow = 3.14 / 2.0;
//       int j = 275;
//       inputTif500[j][i] = 1.0;
//   }

//   //saveMatrixToPGM(inputTif500, "vodstvoSin.pgm");
//   matrix.resize(rows, vector<double>(cols));
//   matrix = inputTif500;
//   
//   for (int i = 0; i < rows; i++) {
//       for (int j = 0; j < cols; j++) {
//           if (matrix[i][j] != 0)
//               matrix[i][j] = downloadedMatrixDataTif500[i][j];
//       }
//   }
//   */

//   for (int i = 0; i < rows; i++) {
//       for (int j = 0; j < cols; j++) {
//           inputTif500[i][j] = 0.0;
//       }
//   }

//   int x1_1 = 0, y1_1 = 0;
//   int x1_2 = cols - 1, y1_2 = 60;

//   auto line1 = bresenhamLine(x1_1, y1_1, x1_2, y1_2);
//   for (const auto& p : line1) {
//       int x = p.first;
//       int y = p.second;
//       if (y >= 0 && y < rows && x >= 0 && x < cols) {
//           inputTif500[y][x] = 1.0;
//       }
//   }

//   int x2_1 = 0, y2_1 = 265;
//   int x2_2 = cols - 1, y2_2 = 115;

//   auto line2 = bresenhamLine(x2_1, y2_1, x2_2, y2_2);
//   for (const auto& p : line2) {
//       int x = p.first;
//       int y = p.second;
//       if (y >= 0 && y < rows && x >= 0 && x < cols) {
//           inputTif500[y][x] = 1.0;
//       }
//   }

//   // -------------------------------------------

//   matrix.resize(rows, std::vector<double>(cols));
//   matrix = inputTif500;

//   for (int i = 0; i < rows; ++i) {
//       for (int j = 0; j < cols; ++j) {
//           if (matrix[i][j] != 0.0) {
//               matrix[i][j] = downloadedMatrixDataTif500[i][j];
//           }
//       }
//   }

//   VectorXd xLap(n * n);

//   vector<VectorXd> xLaps(19, VectorXd(n * n));

//   cout << "laplace start" << endl;

//   xLap = solveSchemeLaplace(matrix, downloadedMatrixDataTif500, 300, 300);

//   cout << "laplace end" << endl;

   //double times[19] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

//   auto t0 = std::chrono::steady_clock::now();
//   vector<vector<double>> laplaceSolution(rows, vector<double>(cols));
//   auto t1 = std::chrono::steady_clock::now();
//   double  tim = std::chrono::duration<double>(t1 - t0).count();

//   std::cout << "Time for laplace solution: " << tim << " seconds" << std::endl;
//   
//   for (int i = 0; i < rows; ++i) {
//       for (int j = 0; j < cols; ++j) {
//           laplaceSolution[i][j] = xLap(i * cols + j);
//       }
//   }
//   //xLap = solveSchemeLaplace(matrix, downloadedMatrixDataTif500, 300, 300);
//   //double omega = 0.1;
//   double omega = 1.99;
//   xLap.resize(n* n);

//   t0 = std::chrono::steady_clock::now();
//   xLap = solveSchemeGS(matrix, downloadedMatrixDataTif500, laplaceSolution, 300, 300, omega);
//   t1 = std::chrono::steady_clock::now();
//   tim = std::chrono::duration<double>(t1 - t0).count();

//   std::cout << "Time for omega = " << omega << ": " << tim << " seconds" << std::endl;

//   saveTXTFor3D(laplaceSolution, 300, h, (omega * 10));
//   /*for (int i = 0; i < 100; i++) {
   //	xLap.resize(n * n);

//       auto t0 = std::chrono::steady_clock::now();
//       xLap = solveSchemeGS(matrix, downloadedMatrixDataTif500, laplaceSolution, 300, 300, omega);
//       auto t1 = std::chrono::steady_clock::now();
//       times[i] = std::chrono::duration<double>(t1 - t0).count();

   //	std::cout << "Time for omega = " << omega << ": " << times[i] << " seconds" << std::endl;

//       saveTXTFor3D(laplaceSolution, 300, h, (omega * 10));

   //	xLaps[i] = xLap;
   //	omega += 0.1;
//       if (omega == 1) {
//           continue;
//       }
//       if (omega > 1.9) {
//           break;
//       }
//   }*/

//   for (int i = 0; i < rows; ++i) {
//       for (int j = 0; j < cols; ++j) {
//           laplaceSolution[i][j] = xLap(i * cols + j);
//       }
//   }

//   vector<vector<double>> underSurfaceWaterl(rows, vector<double>(cols));
//   vector<vector<double>> onSurfaceWaterl(rows, vector<double>(cols));
//   for (int j = 0; j < rows; ++j) {
//       for (int k = 0; k < cols; ++k) {
//           if (laplaceSolution[j][k] < downloadedMatrixDataTif500[j][k] - delta)
//               underSurfaceWaterl[j][k] = 1;
//           else
//               underSurfaceWaterl[j][k] = 0;

//           if (laplaceSolution[j][k] >= downloadedMatrixDataTif500[j][k] - delta)
//               onSurfaceWaterl[j][k] = 1;
//           else
//               onSurfaceWaterl[j][k] = 0;
//       }
//   }
//   /*saveMatrixToPGM(underSurfaceWaterl, "underSurfaceWaterTifAvgSOR.pgm");
//   saveMatrixToPGM(onSurfaceWaterl, "onSurfaceWaterTifAvgSOR.pgm");

//   vector<vector<double>> difCurrentLap(rows, vector<double>(cols));

//   difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.1);
//   saveMatrixToPGM(difCurrentLap, "diff01WaterTifAvgHoresIterSORFebNoErase.pgm");
//   difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.2);
//   saveMatrixToPGM(difCurrentLap, "diff02WaterTifAvgHoresIterSORFebNoErase.pgm");
//   difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.3);
//   saveMatrixToPGM(difCurrentLap, "diff03WaterTifAvgHoresIterSORFebNoErase.pgm");
//   difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.5);
//   saveMatrixToPGM(difCurrentLap, "diff05WaterTifAvgHoresIterSORFebNoErase.pgm");
//   difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.7);
//   saveMatrixToPGM(difCurrentLap, "diff07WaterTifAvgHoresIterSORFebNoErase.pgm");
//   difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 1.0);
//   saveMatrixToPGM(difCurrentLap, "diff10WaterTifAvgHoresIterSORFebNoErase.pgm");*/

//   //saveMatrixToPGM(laplaceSolution, "SeptZacatPodmienkLaplaceSolutionInputTifSOR.pgm");
//   ////saveTXTFor3D(laplaceSolution, 300, h, -5);

//   //ofstream file1;
//   //std::string filenameCurrentTXT1 = "SeptZacatPodmienkLaplaceSolutionInputTifSORIterLast.txt";

//   //file1.open(filenameCurrentTXT1, ios::out);

//   //for (int i = 0; i < n; ++i) {
//   //    for (int j = 0; j < n; ++j) {
//   //        file1 << i * h << " " << j * h << " " << xLap(i * n + j) << endl;
//   //    }
//   //}
//   // 
//   // 
   //																																				//in general safe, uncoment when we dont want to save times for each omega
//   saveMatrixToPGM(underSurfaceWaterl, "underSurfaceSin2PSORV2.pgm");
//   saveMatrixToPGM(onSurfaceWaterl, "onSurfaceSin2PSORV2.pgm");

//   vector<vector<double>> difCurrentLap(rows, vector<double>(cols));

//   difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.1);
//   saveMatrixToPGM(difCurrentLap, "diff01Sin2PSORV2FebNoErase.pgm");
//   difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.2);
//   saveMatrixToPGM(difCurrentLap, "diff02Sin2PSORV2FebNoErase.pgm");
//   difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.3);
//   saveMatrixToPGM(difCurrentLap, "diff03Sin2PSORV2FebNoErase.pgm");
//   difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.5);
//   saveMatrixToPGM(difCurrentLap, "diff0Sinl2PSORV2FebNoErase.pgm");
//   difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.7);
//   saveMatrixToPGM(difCurrentLap, "diff07Sin2PSORV2FebNoErase.pgm");
//   difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 1.0);
//   saveMatrixToPGM(difCurrentLap, "diff10Sin2PSORV2FebNoErase.pgm");

//   saveMatrixToPGM(laplaceSolution, "RealSeptZacatPodmienkPSORV2InputSin2PSORV2.pgm");
//   saveTXTFor3D(laplaceSolution, 300, h, -5);

//   ofstream file1;
//   //std::string filenameCurrentTXT1 = "SeptZacatPodmienkLaplaceSolutionInputTifSORIterLast.txt";
//   std::string filenameCurrentTXT1 = "RealSeptZacatPodmienkPSORV2InpuSinl2PSORV2IterLast.txt";

//   file1.open(filenameCurrentTXT1, ios::out);

//   for (int i = 0; i < n; ++i) {
//       for (int j = 0; j < n; ++j) {
//           file1 << i * h << " " << j * h << " " << xLap(i * n + j) << endl;
//       }
//   }

//   file1.close();

//   return 0;

                                  //new sin end
    vector<vector<double>> laplaceSolution(rows, vector<double>(cols));

    VectorXd xLap(n * n);
    xLap = solveSchemeLaplace(matrix, downloadedMatrixDataTif500, 1875, 1875);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            laplaceSolution[i][j] = xLap(i * cols + j);
        }
    }

    vector<vector<double>> underSurfaceWaterl(rows, vector<double>(cols));
    vector<vector<double>> onSurfaceWaterl(rows, vector<double>(cols));
    for (int j = 0; j < rows; ++j) {
        for (int k = 0; k < cols; ++k) {
            if (laplaceSolution[j][k] < downloadedMatrixDataTif500[j][k] - delta)
                underSurfaceWaterl[j][k] = 1;
            else
                underSurfaceWaterl[j][k] = 0;

            if (laplaceSolution[j][k] >= downloadedMatrixDataTif500[j][k] - delta)
                onSurfaceWaterl[j][k] = 1;
            else
                onSurfaceWaterl[j][k] = 0;
        }
    }

    saveMatrixToPGM(underSurfaceWaterl, "underSurfaceWaterLaplaceCASNoErase.pgm");
    saveMatrixToPGM(onSurfaceWaterl, "onSurfaceWaterLaplaceCASNoErase.pgm");

    vector<vector<double>> difCurrentLap(rows, vector<double>(cols));

    difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.1);
    saveMatrixToPGM(difCurrentLap, "diff01WaterLaplaceCASNoErase.pgm");
    difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.2);
    saveMatrixToPGM(difCurrentLap, "diff02WaterLaplaceCASNoErase.pgm");
    difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.3);
    saveMatrixToPGM(difCurrentLap, "diff03WaterLaplaceCASNoErase.pgm");
    difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.5);
    saveMatrixToPGM(difCurrentLap, "diff05WaterLaplaceCASNoErase.pgm");
    difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 0.7);
    saveMatrixToPGM(difCurrentLap, "diff07WaterLaplaceCASNoErase.pgm");
    difCurrentLap = compareValuesV2(laplaceSolution, downloadedMatrixDataTif500, 1.0);
    saveMatrixToPGM(difCurrentLap, "diff10WaterLaplaceCASNoErase.pgm");

    double minValue = 200;
    double maxValue = matrix[0][0];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((i == 0 && j == 0) || matrix[i][j] == 0) {
                continue;
            }
            else {
                if (minValue > matrix[i][j])
                    minValue = matrix[i][j];
                if (maxValue < matrix[i][j])
                    maxValue = matrix[i][j];
            }

        }
    }

    cout << "min and max value input matrix:" << endl;
    cout << minValue << " " << maxValue << endl;

    minValue = 200;
    maxValue = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((i == 0 && j == 0) || laplaceSolution[i][j] == 0) {
                continue;
            }
            else {
                if (minValue > laplaceSolution[i][j])
                    minValue = laplaceSolution[i][j];
                if (maxValue < laplaceSolution[i][j])
                    maxValue = laplaceSolution[i][j];
            }
        }
    }

    cout << "min and max value u0 matrix:" << endl;
    cout << minValue << " " << maxValue << endl;

    /*vector<vector<double>> differnce = compareValues(inputMatrix, inputMatrix);

    saveMatrixToPGM(inputMatrix, "matInput.pgm");

    cout << "diff end" << endl;
    saveMatrixToPGM(differnce, "diffInput.pgm");
    cout << "diff end" << endl;*/
    // Call the function to solve the membrane system

    //std::vector<std::pair<int, int>> points = bresenhamLine(x1, y1, x2, y2);


    //for (int i = 0; i < rows; i++) {
    //    for (int j = 0; j < cols; j++) {
    //        if (i == 0) {
    //            //matrix[i][j] = g(j * h);
    //            matrix[i][j] = 0;
    //        }
    //        else if (j == 0) {
    //            //matrix[i][j] = g(i * h);
    //            matrix[i][j] = 0;
    //        }
    //        else if (i == n - 1) {
    //            //matrix[i][j] = g(j * h);
    //            matrix[i][j] = 0;
    //        }
    //        else if (j == n - 1) {
    //            //matrix[i][j] = g(i * h);
    //            matrix[i][j] = 0;

    //        }
    //        else {
    //            matrix[i][j] = 100.0;
    //        }
    //        //matrix[i][j] = 100.0;
    //    }
    //}

    //for (const auto& point : line1) {
    //    int x = point.first;
    //    int y = point.second;
    //    if (x >= 0 && x < 30 && y >= 0 && y < n) {
    //        matrix[x][y] = 10; // Учитываем, что y — строка, x — столбец
    //    }
    //}

    /*for (const auto& point : line2) {
        int x = point.first;
        int y = point.second;
        if (x >= 0 && x < n && y >= 0 && y < n) {
            matrix[x][y] = 0;
        }
    }*/


    //Eigen::initParallel();
    VectorXd x(n * n);

    //#pragma omp parallel for

        /*for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0) {
                    A.insert(j, j) = 1.0;
                    b(j) = g(j * h);
                }
                else if (j == 0) {
                    A.insert(i * n, i * n) = 1.0;
                    b(i * n) = g(i * h);
                }
                else if (i == n - 1) {
                    A.insert(i * n + j, i * n + j) = 1.0;
                    b(i * n + j) = g(j * h);
                }
                else if (j == n - 1) {
                    A.insert(i * n + j, i * n + j) = 1.0;
                    b(i * n + j) = g(i * h);
                }
                else {
                    A.insert(i * n + j, i * n + j) = 4.0;
                    A.insert(i * n + j, i * n + j + 1) = -1.0;
                    A.insert(i * n + j, i * n + j - 1) = -1.0;
                    A.insert(i * n + j, (i + 1) * n + j) = -1.0;
                    A.insert(i * n + j, (i - 1) * n + j) = -1.0;
                    b(i * n + j) = 0.0;
                }
            }
        }*/

    x = solveScheme(matrix, laplaceSolution, n);


    vector<vector<double>> matrixFinal(rows, vector<double>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrixFinal[i][j] = x(i * cols + j);
        }
    }

    /*minValue = 1000;
    maxValue = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((i == 0 && j == 0) || matrixFinal[i][j] == 0) {
                continue;
            }
            else {
                if (minValue > matrixFinal[i][j])
                    minValue = matrixFinal[i][j];
                if (maxValue < matrixFinal[i][j])
                    maxValue = matrixFinal[i][j];
            }

        }
    }


    cout << "min and max value solution iter 0 and u^N-1 pre Iter1:" << endl;
    cout << minValue << " " << maxValue << endl;*/

    vector<vector<double>> matrixFinalPrev = compareValues3(matrixFinal, downloadedMatrixDataTif500);

    h = 1.0;
    double L2Norm = 0.0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            L2Norm += h * h * pow(matrixFinalPrev[i][j] - laplaceSolution[i][j], 2);
        }
    }

    vector<vector<double>> underSurfaceWater1(rows, vector<double>(cols));
    vector<vector<double>> onSurfaceWater1(rows, vector<double>(cols));
    for (int j = 0; j < rows; ++j) {
        for (int k = 0; k < cols; ++k) {
            if (matrixFinalPrev[j][k] < downloadedMatrixDataTif500[j][k] - delta)
                underSurfaceWater1[j][k] = 1;
            else
                underSurfaceWater1[j][k] = 0;

            if (matrixFinalPrev[j][k] >= downloadedMatrixDataTif500[j][k] - delta)
                onSurfaceWater1[j][k] = 1;
            else
                onSurfaceWater1[j][k] = 0;
        }
    }
    saveMatrixToPGM(underSurfaceWater1, "underSurfaceWaterTifAvgHoresIterMayNoErase" + std::to_string(1) + ".pgm");
    saveMatrixToPGM(onSurfaceWater1, "onSurfaceWaterTifAvgHoresIterMayNoErase" + std::to_string(1) + ".pgm");

    double tL2 = sqrt(L2Norm);
    double L2Norm0 = tL2;
    cout << endl;
    cout << "L2 norma " << L2Norm0 << endl;

    double xMin = 0.0, xMax = 30.0;
    double yMin = 0.0, yMax = 30.0;

    ofstream file;
    //file.open("SeptZacatPodmienkDTM.txt", ios::out);
    //file.open("solutionWatersSept.txt", ios::out);

                                                                                                                                                //uncomment when do hydrological model
    file.open("SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresMayNoErase.txt", ios::out);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file << i * h << " " << j * h << " " << x(i * n + j) << endl;
        }
    }

    file.close();

    //saveTXTFor3D(matrixFinalPrev, n, h, 0);
                                                                                                                                                //uncomment when do hydrological model        
    vector<vector<double>> dif = compareValues(matrixFinalPrev, downloadedMatrixDataTif500, 0.1);

    saveMatrixToPGM(dif, "diff01SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresMayNoErase.pgm");

    saveMatrixToPGM(matrixFinalPrev, "SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresMayNoErase.pgm");

    saveMatrixToFile(matrixFinalPrev, "SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresMayNoErase.txt");
    //printMatrix(matrix);

    double sum = 0.0;

    /*filename = "Hores_square_DTM_data.pgm";

    vector<vector<double>> downloadedMatrixData = readPGMToMatrix(filename);*/

    //vector<vector<double>> matrixIter1 = compareValues2(matrixFinal, downloadedMatrixData, matrix);
    //saveMatrixToPGM(matrixIter1, "inputMatrixIter1.pgm");



    //matrix = loadMatrixFromFile(filename);

    /*minValue = 200;
    maxValue = matrixIter1[0][0];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrixIter1[i][j] == 0) {
                continue;
            }
            else {
                if (minValue > matrixIter1[i][j])
                    minValue = matrixIter1[i][j];
                if (maxValue < matrixIter1[i][j])
                    maxValue = matrixIter1[i][j];
            }

        }
    }

    cout << "min and max value input matrix Iter1:" << endl;
    cout << minValue << " " << maxValue << endl;*/

    /*vector<vector<double>> differnce = compareValues(inputMatrix, inputMatrix);

    saveMatrixToPGM(inputMatrix, "matInput.pgm");

    cout << "diff end" << endl;
    saveMatrixToPGM(differnce, "diffInput.pgm");
    cout << "diff end" << endl;*/
    // Call the function to solve the membrane system

    //std::vector<std::pair<int, int>> points = bresenhamLine(x1, y1, x2, y2);


    //for (int i = 0; i < rows; i++) {
    //    for (int j = 0; j < cols; j++) {
    //        if (i == 0) {
    //            //matrix[i][j] = g(j * h);
    //            matrix[i][j] = 0;
    //        }
    //        else if (j == 0) {
    //            //matrix[i][j] = g(i * h);
    //            matrix[i][j] = 0;
    //        }
    //        else if (i == n - 1) {
    //            //matrix[i][j] = g(j * h);
    //            matrix[i][j] = 0;
    //        }
    //        else if (j == n - 1) {
    //            //matrix[i][j] = g(i * h);
    //            matrix[i][j] = 0;

    //        }
    //        else {
    //            matrix[i][j] = 100.0;
    //        }
    //        //matrix[i][j] = 100.0;
    //    }
    //}

    //for (const auto& point : line1) {
    //    int x = point.first;
    //    int y = point.second;
    //    if (x >= 0 && x < 30 && y >= 0 && y < n) {
    //        matrix[x][y] = 10; // Учитываем, что y — строка, x — столбец
    //    }
    //}

    /*for (const auto& point : line2) {
        int x = point.first;
        int y = point.second;
        if (x >= 0 && x < n && y >= 0 && y < n) {
            matrix[x][y] = 0;
        }
    }*/


    //Eigen::initParallel();
    //SparseMatrix<double> A(n * n, n * n);
    //SparseMatrix<double> temp(n * n, n * n);
    //VectorXd b(n * n), x(n * n);




    //h = (a - 0.0) / (double)(rows - 1);

    //A.reserve(Eigen::VectorXi::Constant(n* n, 5));


//    A.reserve(Eigen::VectorXi::Constant(n * n, 5));
//
//#pragma omp parallel for
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < cols; ++j) {
//            int idx = i * cols + j;
//            if (matrixIter1[i][j] != 0) {
//                A.insert(idx, idx) = 1.0;
//                b(idx) = matrixIter1[i][j];
//            }
//            else {
//                A.insert(idx, idx) = 5.0;
//                if (j + 1 > cols - 1) { //2
//                    if (i - 1 < 0) { //5
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = matrixFinal[i][j];
//                        //b(idx) = 0;
//                        continue;
//                    }
//                    if (i + 1 > rows - 1) { //6
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx - cols) = -2.0;
//                        b(idx) = matrixFinal[i][j];
//                        //b(idx) = 0;
//                        continue;
//                    }
//                    A.insert(idx, idx - 1) = -2.0;
//                    A.insert(idx, idx + cols) = -1.0;
//                    A.insert(idx, idx - cols) = -1.0;
//                    b(idx) = matrixFinal[i][j];
//                    //b(idx) = 0;
//                    continue;
//                }
//                if (i - 1 < 0) { // 1
//                    if (j + 1 > cols - 1) { // 5
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = matrixFinal[i][j];
//                        //b(idx) = 0;
//                        continue;
//                    }
//                    if (j - 1 < 0) { //8
//                        A.insert(idx, idx + 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = matrixFinal[i][j];
//                        //b(idx) = 0;
//                        continue;
//                    }
//                    A.insert(idx, idx - 1) = -1.0;
//                    A.insert(idx, idx + cols) = -2.0;
//                    A.insert(idx, idx + 1) = -1.0;
//                    b(idx) = matrixFinal[i][j];
//                    //b(idx) = 0;
//                    continue;
//                }
//                if (j - 1 < 0) { //4
//                    if (i - 1 < 0) { //8
//                        A.insert(idx, idx + 1) = -2.0;
//                        A.insert(idx, idx + cols) = -2.0;
//                        b(idx) = matrixFinal[i][j];
//                        //b(idx) = 0;
//                        continue;
//                    }
//                    if (i + 1 > rows - 1) { //7
//                        A.insert(idx, idx - cols) = -2.0;
//                        A.insert(idx, idx + 1) = -2.0;
//                        b(idx) = matrixFinal[i][j];
//                        //b(idx) = 0;
//                        continue;
//                    }
//                    A.insert(idx, idx - cols) = -1.0;
//                    A.insert(idx, idx + cols) = -1.0;
//                    A.insert(idx, idx + 1) = -2.0;
//                    b(idx) = matrixFinal[i][j];
//                    //b(idx) = 0;
//                    continue;
//                }
//                if (i + 1 > rows - 1) { // 3
//                    if (j - 1 < 0) { // 7
//                        A.insert(idx, idx - cols) = -2.0;
//                        A.insert(idx, idx + 1) = -2.0;
//                        b(idx) = matrixFinal[i][j];
//                        //b(idx) = 0;
//                        continue;
//                    }
//                    if (j + 1 > cols - 1) { //6
//                        A.insert(idx, idx - 1) = -2.0;
//                        A.insert(idx, idx - cols) = -2.0;
//                        b(idx) = matrixFinal[i][j];
//                        //b(idx) = 0;
//                        continue;
//                    }
//                    A.insert(idx, idx - cols) = -2.0;
//                    A.insert(idx, idx - 1) = -1.0;
//                    A.insert(idx, idx + 1) = -1.0;
//                    b(idx) = matrixFinal[i][j];
//                    //b(idx) = 0;
//                    continue;
//                }
//                A.insert(idx, idx + 1) = -1.0;//i,j+1
//                A.insert(idx, idx - 1) = -1.0;//i,j-1
//                A.insert(idx, idx + cols) = -1.0;//i+1,j
//                A.insert(idx, idx - cols) = -1.0;//i-1,j
//                b(idx) = matrixFinal[i][j];
//                //b(idx) = 0;
//            }
//        }
//    }

    /*for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0) {
                A.insert(j, j) = 1.0;
                b(j) = g(j * h);
            }
            else if (j == 0) {
                A.insert(i * n, i * n) = 1.0;
                b(i * n) = g(i * h);
            }
            else if (i == n - 1) {
                A.insert(i * n + j, i * n + j) = 1.0;
                b(i * n + j) = g(j * h);
            }
            else if (j == n - 1) {
                A.insert(i * n + j, i * n + j) = 1.0;
                b(i * n + j) = g(i * h);
            }
            else {
                A.insert(i * n + j, i * n + j) = 4.0;
                A.insert(i * n + j, i * n + j + 1) = -1.0;
                A.insert(i * n + j, i * n + j - 1) = -1.0;
                A.insert(i * n + j, (i + 1) * n + j) = -1.0;
                A.insert(i * n + j, (i - 1) * n + j) = -1.0;
                b(i * n + j) = 0.0;
            }
        }
    }*/
    VectorXd xIter1(n * n);
    xIter1 = solveScheme(matrix, matrixFinalPrev, n);

    vector<vector<double>> matrixFinalIter1(rows, vector<double>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrixFinalIter1[i][j] = xIter1(i * cols + j);
        }
    }


    /*minValue = 10000;
    maxValue = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrixFinalIter1[i][j] == 0) {
                continue;
            }
            else {
                if (minValue > matrixFinalIter1[i][j])
                    minValue = matrixFinalIter1[i][j];
                if (maxValue < matrixFinalIter1[i][j])
                    maxValue = matrixFinalIter1[i][j];
            }

        }
    }

    cout << endl;
    cout << "min and max value solution after Iter1 and u^N-1 pre Iter2:" << endl;
    cout << minValue << " " << maxValue << endl;*/

    vector<vector<double>> matrixFinalIter1Prev = compareValues3(matrixFinalIter1, downloadedMatrixDataTif500);

    L2Norm = 0.0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            L2Norm += h * h * pow(matrixFinalIter1Prev[i][j] - matrixFinal[i][j], 2);
        }
    }

    tL2 = sqrt(L2Norm);
    //L2Norm = tL2 / L2Norm0;
    L2Norm = tL2;
    cout << endl;
    cout << "L2 norm solution after Iter1 " << L2Norm << endl;

    saveTXTFor3D(matrixFinalIter1Prev, n, h, 1);

    /*ofstream file;
    file.open("solutionWatersSept.txt", ios::out);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file << i * h << " " << j * h << " " << x(i * n + j) << endl;
        }
    }

    file.close();*/

    //vector<vector<double>> matrixIter2 = compareValues2(matrixFinalIter1, downloadedMatrixData, matrixIter1);
    //saveMatrixToPGM(matrixIter2, "inputMatrixIter2.pgm");



    int counter = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fabs(matrixFinalIter1[i][j] - matrixFinal[i][j]) > 0.000001)
                counter++;
        }
    }

    cout << "dif pixels:" << counter << endl;
    //uncomment next section when do hydrological model
    file.open("SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresMayNoEraseIter1.txt", ios::out);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file << i * h << " " << j * h << " " << xIter1(i * n + j) << endl;
        }
    }

    file.close();

    vector<vector<double>> dif1 = compareValues(matrixFinalIter1, downloadedMatrixDataTif500, 0.1);

    saveMatrixToPGM(dif1, "diff01SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresMayNoEraseIter1.pgm");

    saveMatrixToPGM(matrixFinalIter1, "SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresMayNoEraseIter1.pgm");

    saveMatrixToFile(matrixFinalIter1, "SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresMayNoEraseIter1.txt");
    /*minValue = 10000;
    maxValue = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrixIter2[i][j] == 0) {
                continue;
            }
            else {
                if (minValue > matrixIter2[i][j])
                    minValue = matrixIter2[i][j];
                if (maxValue < matrixIter2[i][j])
                    maxValue = matrixIter2[i][j];
            }

        }
    }

    cout << "min and max value input matrix for Iter2:" << endl;
    cout << minValue << " " << maxValue << endl;*/

    VectorXd xIter2(n * n);
    xIter2 = solveScheme(matrix, matrixFinalIter1Prev, n);

    vector<vector<double>> matrixFinalIter2(rows, vector<double>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrixFinalIter2[i][j] = xIter2(i * cols + j);
        }
    }


    /*minValue = 10000;
    maxValue = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (minValue > matrixFinalIter2[i][j])
                minValue = matrixFinalIter2[i][j];
            if (maxValue < matrixFinalIter2[i][j])
                maxValue = matrixFinalIter2[i][j];

        }
    }

    cout << endl;
    cout << "min and max value solution after Iter2:" << endl;
    cout << minValue << " " << maxValue << endl;*/

    //printMatrix(matrixFinalIter2);

    vector<vector<double>> matrixIterPrev = compareValues3(matrixFinalIter2, downloadedMatrixDataTif500);

    L2Norm = 0.0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            L2Norm += h * h * pow(matrixIterPrev[i][j] - matrixFinalIter1[i][j], 2);
        }
    }

    tL2 = sqrt(L2Norm);
    //L2Norm = tL2 / L2Norm0;
    L2Norm = tL2;
    cout << endl;
    cout << "L2 norm solution after Iter2 " << L2Norm << endl;

    saveTXTFor3D(matrixIterPrev, n, h, 2);

    //vector<vector<double>> matrixIterNext = compareValues2(matrixFinalIter2, downloadedMatrixData, matrixIter2);
    //saveMatrixToPGM(matrixIterNext, "inputMatrixIter3.pgm");




    //vector<vector<double>> matrixIterPrev = matrixFinalIter2;

    counter = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fabs(matrixFinalIter2[i][j] - matrixFinalIter1[i][j]) > 0.000001)
                counter++;
        }
    }

    cout << "dif pixels:" << counter << endl;

    //for iteracie
    VectorXd xIterNext(n * n);
    vector<vector<double>> difCurrent;
    vector<vector<double>> matrixFinalNext(rows, vector<double>(cols));
    vector<vector<double>> matrixFinalPrevNext(rows, vector<double>(cols));
    vector<vector<double>> temp;
    int counter2 = 0;
    for (int i = 1; i <= 10000; i++) {

        xIterNext.resize(n * n);
        xIterNext = solveScheme(matrix, matrixIterPrev, n);

        //vector<vector<double>> matrixFinalNext(rows, vector<double>(cols));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                matrixFinalNext[i][j] = xIterNext(i * cols + j);
            }
        }


        /*minValue = 10000;
        maxValue = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (matrixFinalNext[i][j] == 0) {
                    continue;
                }
                else {
                    if (minValue > matrixFinalNext[i][j])
                        minValue = matrixFinalNext[i][j];
                    if (maxValue < matrixFinalNext[i][j])
                        maxValue = matrixFinalNext[i][j];
                }

            }
        }

        cout << endl;
        cout << "min and max value solution after Iter "<< i + 2 << " and u ^ N - 1 pre Iter " <<  counter2 +2 << " : " << endl;
        cout << minValue << " " << maxValue << endl;*/

        matrixFinalPrevNext = compareValues3(matrixFinalNext, downloadedMatrixDataTif500);

        L2Norm = 0.0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                L2Norm += h * h * pow(matrixFinalPrevNext[i][j] - matrixIterPrev[i][j], 2);
            }
        }

        tL2 = sqrt(L2Norm);
        //L2Norm = tL2 / L2Norm0;
        L2Norm = tL2;
        //cout << endl;
        //cout << "L2 norm solution after Iter "  << i+2 << " " << L2Norm << endl;

        /*ofstream file;
        file.open("solutionWatersSept.txt", ios::out);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                file << i * h << " " << j * h << " " << x(i * n + j) << endl;
            }
        }

        file.close();*/




        //temp = matrixIterNext;
        //matrixIterNext = compareValues2(matrixFinalNext, downloadedMatrixData, temp);
        //saveMatrixToPGM(matrixIterNext, "inputMatrixIter" + std::to_string(counter2 + 4) + ".pgm");


        /*int counter = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (fabs(matrixFinalIter1[i][j] - matrixFinal[i][j]) > 0.000001)
                    counter++;
            }
        }

        cout << "dif pixels:" << counter << endl;*/

        /*std::string filenameCurrentTXT = "SeptZacatPodmienkDTMWithoutCheckIfMatrixIJIsZeroIter" + std::to_string(i+2) + ".txt";

        file.open(filenameCurrentTXT, ios::out);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                file << i * h << " " << j * h << " " << xIter1(i * n + j) << endl;
            }
        }

        file.close();

        difCurrent = compareValues(matrixFinalNext, downloadedMatrixData);

        saveMatrixToPGM(difCurrent, "diff01SeptZacatPodmienkDTMWithoutCheckIfMatrixIJIsZeroIter" + std::to_string(i + 2) + ".pgm");

        saveMatrixToPGM(matrixFinalNext, "SeptZacatPodmienkDTMWithoutCheckIfMatrixIJIsZeroIter" + std::to_string(i + 2) + ".pgm");

        saveMatrixToFile(matrixFinalNext, "SeptZacatPodmienkDTMWithoutCheckIfMatrixIJIsZeroIter" + std::to_string(i + 2) + ".txt");*/

        /*minValue = 10000;
        maxValue = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (matrixIter2[i][j] == 0) {
                    continue;
                }
                else {
                    if (minValue > matrixIterNext[i][j])
                        minValue = matrixIterNext[i][j];
                    if (maxValue < matrixIterNext[i][j])
                        maxValue = matrixIterNext[i][j];
                }

            }
        }

        cout << "min and max value input matrix for Iter " << i+3 << " :" << endl;
        cout << minValue << " " << maxValue << endl;*/

        matrixIterPrev = matrixFinalPrevNext;
        counter2++;


        //new 
        if (counter2 < 200 && counter2 % 100 == 0) {
            cout << endl;
            cout << "L2 norm solution after Iter " << i + 2 << " " << L2Norm << endl;
            vector<vector<double>> underSurfaceWater(rows, vector<double>(cols));
            vector<vector<double>> onSurfaceWater(rows, vector<double>(cols));
            for (int j = 0; j < rows; ++j) {
                for (int k = 0; k < cols; ++k) {
                    if (matrixIterPrev[j][k] < downloadedMatrixDataTif500[j][k] - delta)
                        underSurfaceWater[j][k] = 1;
                    else
                        underSurfaceWater[j][k] = 0;

                    if (matrixIterPrev[j][k] >= downloadedMatrixDataTif500[j][k] - delta)
                        onSurfaceWater[j][k] = 1;
                    else
                        onSurfaceWater[j][k] = 0;
                }
            }
            saveMatrixToPGM(underSurfaceWater, "underSurfaceWaterTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
            saveMatrixToPGM(onSurfaceWater, "onSurfaceWaterTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");

            difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.1);
            saveMatrixToPGM(difCurrent, "diff01SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
            difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.2);
            saveMatrixToPGM(difCurrent, "diff02SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
            difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.3);
            saveMatrixToPGM(difCurrent, "diff03SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
            difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.5);
            saveMatrixToPGM(difCurrent, "diff05SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
            difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.7);
            saveMatrixToPGM(difCurrent, "diff07SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
            difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 1.0);
            saveMatrixToPGM(difCurrent, "diff10SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
        }

        //save data every 100 iters
        if (counter2 % 1000 == 0) {
            //uncomment when do hydrological model
//saveTXTFor3D(matrixIterPrev, n, h, counter2 + 3);
            cout << endl;
            cout << "L2 norm solution after Iter " << i + 2 << " " << L2Norm << endl;
            saveMatrixToPGM(matrixIterPrev, "SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
            difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.1);
            saveMatrixToPGM(matrixIterPrev, "SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
            difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.2);
            saveMatrixToPGM(difCurrent, "diff01SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
            difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.3);
            saveMatrixToPGM(difCurrent, "diff03SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
            difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.5);
            saveMatrixToPGM(difCurrent, "diff05SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
            difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.7);
            saveMatrixToPGM(difCurrent, "diff07SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
            difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 1);
            saveMatrixToPGM(difCurrent, "diff10SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");

            vector<vector<double>> underSurfaceWater(rows, vector<double>(cols));
            vector<vector<double>> onSurfaceWater(rows, vector<double>(cols));
            for (int j = 0; j < rows; ++j) {
                for (int k = 0; k < cols; ++k) {
                    if (matrixIterPrev[j][k] < downloadedMatrixDataTif500[j][k] - delta)
                        underSurfaceWater[j][k] = 1;
                    else
                        underSurfaceWater[j][k] = 0;

                    if (matrixIterPrev[j][k] >= downloadedMatrixDataTif500[j][k] - delta)
                        onSurfaceWater[j][k] = 1;
                    else
                        onSurfaceWater[j][k] = 0;
                }
            }
            saveMatrixToPGM(underSurfaceWater, "underSurfaceWaterTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
            saveMatrixToPGM(onSurfaceWater, "onSurfaceWaterTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
            saveTXTFor3D(matrixIterPrev, n, h, counter2 + 3);

            //toto mozne bude deletnut
/*vector<vector<double>> underSurfaceWater(rows, vector<double>(cols));
vector<vector<double>> onSurfaceWater(rows, vector<double>(cols));
for (int j = 0; j < rows; ++j) {
    for (int k = 0; k < cols; ++k) {
        if (matrixIterPrev[j][k] < downloadedMatrixDataTif500[j][k] - delta)
            underSurfaceWater[j][k] = 1;
        else
            underSurfaceWater[j][k] = 0;

        if (matrixIterPrev[j][k] >= downloadedMatrixDataTif500[j][k] - delta)
            onSurfaceWater[j][k] = 1;
        else
            onSurfaceWater[j][k] = 0;
    }
}
saveMatrixToPGM(underSurfaceWater, "underSurfaceWaterSin3Iter" + std::to_string(counter2 + 3) + ".pgm");
saveMatrixToPGM(onSurfaceWater, "onSurfaceWaterSin3Iter" + std::to_string(counter2 + 3) + ".pgm"); */

        }

        if (L2Norm < 0.01)
            break;
    }

    vector<vector<double>> underSurfaceWater(rows, vector<double>(cols));
    vector<vector<double>> onSurfaceWater(rows, vector<double>(cols));
    for (int j = 0; j < rows; ++j) {
        for (int k = 0; k < cols; ++k) {
            if (matrixIterPrev[j][k] < downloadedMatrixDataTif500[j][k] - delta)
                underSurfaceWater[j][k] = 1;
            else
                underSurfaceWater[j][k] = 0;

            if (matrixIterPrev[j][k] >= downloadedMatrixDataTif500[j][k] - delta)
                onSurfaceWater[j][k] = 1;
            else
                onSurfaceWater[j][k] = 0;
        }
    }
    saveMatrixToPGM(underSurfaceWater, "underSurfaceWaterTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
    saveMatrixToPGM(onSurfaceWater, "onSurfaceWaterTifAvgHoresIterNoEraseMay" + std::to_string(counter2 + 3) + ".pgm");
    //uncomment when do hydrological model
    std::string filenameCurrentTXT = "SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresNoEraseMay10e-2Iter" + std::to_string(counter2 + 3) + ".txt";

    file.open(filenameCurrentTXT, ios::out);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file << i * h << " " << j * h << " " << xIterNext(i * n + j) << endl;
        }
    }

    file.close();

    difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.7);

    //saveTXTFor3D(matrixIterPrev, n, h, counter2 + 3);

    //saveMatrixToPGM(matrixIterNext, "inputMatrixIter" + std::to_string(counter2 + 4) + ".pgm");
                                                                                                                                                //uncomment when do hydrological model
    saveMatrixToPGM(difCurrent, "diff07SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresNoEraseMay10e-2Iter" + std::to_string(counter2 + 3) + ".pgm");

    difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.5);
    saveMatrixToPGM(difCurrent, "diff05SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresNoEraseMay10e-2Iter" + std::to_string(counter2 + 3) + ".pgm");

    difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.3);
    saveMatrixToPGM(difCurrent, "diff03SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresNoEraseMay10e-2Iter" + std::to_string(counter2 + 3) + ".pgm");

    difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.2);
    saveMatrixToPGM(difCurrent, "diff02SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresNoEraseMay10e-2Iter" + std::to_string(counter2 + 3) + ".pgm");

    difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 0.1);
    saveMatrixToPGM(difCurrent, "diff01SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresNoEraseMay10e-2Iter" + std::to_string(counter2 + 3) + ".pgm");

    difCurrent = compareValues(matrixIterPrev, downloadedMatrixDataTif500, 1);
    saveMatrixToPGM(difCurrent, "diff1SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresNoEraseMay10e-2Iter" + std::to_string(counter2 + 3) + ".pgm");

    saveMatrixToPGM(matrixIterPrev, "SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresNoEraseMay10e-2Iter" + std::to_string(counter2 + 3) + ".pgm");

    saveMatrixToFile(matrixIterPrev, "SeptZacatPodmienkLaplaceSolutionWithObstacleChangesInSolutionTifAvgHoresNoEraseMay10e-2Iter" + std::to_string(counter2 + 3) + ".txt");


    return 0;
}