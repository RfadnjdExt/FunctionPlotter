#include "FunctionPlotter.h"

// ============================================
// IMPLEMENTASI MathEvaluator
// ============================================

MathEvaluator::MathEvaluator(string expr) : expression(expr) {
    // Ganti operator ^ dengan **
    size_t pos = 0;
    while ((pos = expression.find("^", pos)) != string::npos) {
        expression.replace(pos, 1, "**");
        pos += 2;
    }
}

double MathEvaluator::parseNumber(const string& str, size_t& pos) {
    size_t start = pos;
    bool hasDecimal = false;
    
    while (pos < str.length() && (isdigit(str[pos]) || str[pos] == '.')) {
        if (str[pos] == '.') {
            if (hasDecimal) break;
            hasDecimal = true;
        }
        pos++;
    }
    
    return stod(str.substr(start, pos - start));
}

double MathEvaluator::parseFactor(const string& str, size_t& pos, double x, double y) {
    // Skip whitespace
    while (pos < str.length() && isspace(str[pos])) pos++;
    
    if (pos >= str.length()) return 0;
    
    // Unary minus
    if (str[pos] == '-') {
        pos++;
        return -parseFactor(str, pos, x, y);
    }
    
    // Parentheses
    if (str[pos] == '(') {
        pos++;
        double result = parseExpression(str, pos, x, y);
        if (pos < str.length() && str[pos] == ')') pos++;
        return result;
    }
    
    // Variable x
    if (str[pos] == 'x') {
        pos++;
        return x;
    }
    
    // Variable y
    if (str[pos] == 'y') {
        pos++;
        return y;
    }
    
    // Mathematical constants
    if (str.substr(pos, 2) == "pi") {
        pos += 2;
        return M_PI;
    }
    
    if (str[pos] == 'e' && (pos + 1 >= str.length() || !isalpha(str[pos + 1]))) {
        pos++;
        return M_E;
    }
    
    // Inverse Trigonometric Functions
    if (str.substr(pos, 4) == "asin") {
        pos += 4;
        return asin(parseFactor(str, pos, x, y));
    }
    if (str.substr(pos, 4) == "acos") {
        pos += 4;
        return acos(parseFactor(str, pos, x, y));
    }
    if (str.substr(pos, 4) == "atan") {
        pos += 4;
        return atan(parseFactor(str, pos, x, y));
    }
    
    // Hyperbolic Functions
    if (str.substr(pos, 4) == "sinh") {
        pos += 4;
        return sinh(parseFactor(str, pos, x, y));
    }
    if (str.substr(pos, 4) == "cosh") {
        pos += 4;
        return cosh(parseFactor(str, pos, x, y));
    }
    if (str.substr(pos, 4) == "tanh") {
        pos += 4;
        return tanh(parseFactor(str, pos, x, y));
    }

    // Standard Trigonometric Functions
    if (str.substr(pos, 3) == "sin") {
        pos += 3;
        return sin(parseFactor(str, pos, x, y));
    }
    if (str.substr(pos, 3) == "cos") {
        pos += 3;
        return cos(parseFactor(str, pos, x, y));
    }
    if (str.substr(pos, 3) == "tan") {
        pos += 3;
        return tan(parseFactor(str, pos, x, y));
    }
    if (str.substr(pos, 3) == "log") {
        pos += 3;
        return log(parseFactor(str, pos, x, y));
    }
    if (str.substr(pos, 2) == "ln") {
        pos += 2;
        return log(parseFactor(str, pos, x, y));
    }
    if (str.substr(pos, 3) == "exp") {
        pos += 3;
        return exp(parseFactor(str, pos, x, y));
    }
    if (str.substr(pos, 4) == "sqrt") {
        pos += 4;
        return sqrt(parseFactor(str, pos, x, y));
    }
    if (str.substr(pos, 3) == "abs") {
        pos += 3;
        return abs(parseFactor(str, pos, x, y));
    }
    
    // Number
    if (isdigit(str[pos]) || str[pos] == '.') {
        return parseNumber(str, pos);
    }
    
    return 0;
}

double MathEvaluator::parseTerm(const string& str, size_t& pos, double x, double y) {
    double result = parseFactor(str, pos, x, y);
    
    while (pos < str.length()) {
        // Skip whitespace
        while (pos < str.length() && isspace(str[pos])) pos++;
        
        if (pos >= str.length()) break;
        
        // Power operator **
        if (pos + 1 < str.length() && str[pos] == '*' && str[pos + 1] == '*') {
            pos += 2;
            result = pow(result, parseFactor(str, pos, x, y));
        }
        // Multiplication
        else if (str[pos] == '*') {
            pos++;
            result *= parseFactor(str, pos, x, y);
        }
        // Division
        else if (str[pos] == '/') {
            pos++;
            double divisor = parseFactor(str, pos, x, y);
            if (divisor == 0) return numeric_limits<double>::quiet_NaN();
            result /= divisor;
        }
        else {
            break;
        }
    }
    
    return result;
}

double MathEvaluator::parseExpression(const string& str, size_t& pos, double x, double y) {
    double result = parseTerm(str, pos, x, y);
    
    while (pos < str.length()) {
        // Skip whitespace
        while (pos < str.length() && isspace(str[pos])) pos++;
        
        if (pos >= str.length() || str[pos] == ')') break;
        
        // Addition
        if (str[pos] == '+') {
            pos++;
            result += parseTerm(str, pos, x, y);
        }
        // Subtraction
        else if (str[pos] == '-') {
            pos++;
            result -= parseTerm(str, pos, x, y);
        }
        else {
            break;
        }
    }
    
    return result;
}

double MathEvaluator::evaluate(double x) {
    size_t pos = 0;
    return parseExpression(expression, pos, x, 0);
}

double MathEvaluator::evaluate(double x, double y) {
    size_t pos = 0;
    return parseExpression(expression, pos, x, y);
}

// ============================================
// IMPLEMENTASI Plotter2D
// ============================================

Plotter2D::Plotter2D(string funcName) : functionName(funcName) {}

void Plotter2D::addPoint(double x, double y) {
    Point2D p = {x, y};
    points.push_back(p);
}

void Plotter2D::generateData(MathEvaluator& evaluator, Range range) {
    points.clear();
    
    for (double x = range.min; x <= range.max; x += range.step) {
        double y = evaluator.evaluate(x);
        
        if (!isnan(y) && !isinf(y)) {
            addPoint(x, y);
        }
    }
}

void Plotter2D::plotToSVG(const string& filename) {
    if (points.empty()) return;
    
    ofstream file(filename);
    
    // Find min/max untuk scaling
    double minX = points[0].x, maxX = points[0].x;
    double minY = points[0].y, maxY = points[0].y;
    
    for (const auto& p : points) {
        minX = min(minX, p.x);
        maxX = max(maxX, p.x);
        minY = min(minY, p.y);
        maxY = max(maxY, p.y);
    }
    
    // SVG dimensions
    int width = 800, height = 600;
    int margin = 50;
    
    file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    file << "<svg width=\"" << width << "\" height=\"" << height << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    file << "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";
    
    // Grid
    file << "<g stroke=\"#e0e0e0\" stroke-width=\"1\">\n";
    for (int i = 0; i <= 10; i++) {
        int x = margin + i * (width - 2 * margin) / 10;
        int y = margin + i * (height - 2 * margin) / 10;
        file << "<line x1=\"" << x << "\" y1=\"" << margin << "\" x2=\"" << x << "\" y2=\"" << height - margin << "\"/>\n";
        file << "<line x1=\"" << margin << "\" y1=\"" << y << "\" x2=\"" << width - margin << "\" y2=\"" << y << "\"/>\n";
    }
    file << "</g>\n";
    
    // Axes
    int zeroX = margin + (0 - minX) / (maxX - minX) * (width - 2 * margin);
    int zeroY = height - margin - (0 - minY) / (maxY - minY) * (height - 2 * margin);
    file << "<line x1=\"" << margin << "\" y1=\"" << zeroY << "\" x2=\"" << width - margin << "\" y2=\"" << zeroY << "\" stroke=\"black\" stroke-width=\"2\"/>\n";
    file << "<line x1=\"" << zeroX << "\" y1=\"" << margin << "\" x2=\"" << zeroX << "\" y2=\"" << height - margin << "\" stroke=\"black\" stroke-width=\"2\"/>\n";
    
    // Plot curve
    file << "<polyline points=\"";
    for (const auto& p : points) {
        int x = margin + (p.x - minX) / (maxX - minX) * (width - 2 * margin);
        int y = height - margin - (p.y - minY) / (maxY - minY) * (height - 2 * margin);
        file << x << "," << y << " ";
    }
    file << "\" fill=\"none\" stroke=\"#4f46e5\" stroke-width=\"3\"/>\n";
    
    // Title
    file << "<text x=\"" << width / 2 << "\" y=\"30\" font-size=\"20\" text-anchor=\"middle\" font-weight=\"bold\">";
    file << "f(x) = " << functionName << "</text>\n";
    
    file << "</svg>\n";
    file.close();
    
    cout << "Grafik disimpan ke " << filename << endl;
}

void Plotter2D::plotToConsole() {
    if (points.empty()) return;
    
    cout << "\n========== GRAFIK 2D ==========\n";
    cout << "Fungsi: f(x) = " << functionName << "\n";
    cout << "Jumlah titik: " << points.size() << "\n\n";
    
    // Tampilkan beberapa titik
    cout << "Beberapa titik pada kurva:\n";
    cout << "    x    |    y    \n";
    cout << "---------|----------\n";
    
    int step = max(1, (int)(points.size() / 10));
    for (size_t i = 0; i < points.size(); i += step) {
        printf("%8.2f | %8.2f\n", points[i].x, points[i].y);
    }
}

// ============================================
// IMPLEMENTASI Plotter3D
// ============================================

Plotter3D::Plotter3D(string funcName, int res) : functionName(funcName), resolution(res) {}

void Plotter3D::generateSurface(MathEvaluator& evaluator, Range range) {
    points.clear();
    
    for (int i = 0; i <= resolution; i++) {
        for (int j = 0; j <= resolution; j++) {
            double x = range.min + (range.max - range.min) * i / resolution;
            double y = range.min + (range.max - range.min) * j / resolution;
            double z = evaluator.evaluate(x, y);
            
            if (!isnan(z) && !isinf(z)) {
                Point3D p = {x, y, z};
                points.push_back(p);
            }
        }
    }
}

void Plotter3D::exportToOBJ(const string& filename) {
    ofstream file(filename);
    
    file << "# OBJ file generated by FunctionPlotter\n";
    file << "# Function: f(x,y) = " << functionName << "\n\n";
    
    // Write vertices
    for (const auto& p : points) {
        file << "v " << p.x << " " << p.z << " " << p.y << "\n";
    }
    
    // Write faces
    for (int i = 0; i < resolution; i++) {
        for (int j = 0; j < resolution; j++) {
            int a = i * (resolution + 1) + j + 1;
            int b = a + 1;
            int c = (i + 1) * (resolution + 1) + j + 1;
            int d = c + 1;
            
            file << "f " << a << " " << b << " " << c << "\n";
            file << "f " << b << " " << d << " " << c << "\n";
        }
    }
    
    file.close();
    cout << "Model 3D disimpan ke " << filename << endl;
}

// ============================================
// IMPLEMENTASI NumericalCalculus
// ============================================

double NumericalCalculus::calculateDerivative(MathEvaluator& evaluator, double x, double h) {
    // Central Difference Method: (f(x+h) - f(x-h)) / 2h
    // Error order: O(h^2)
    double f_plus = evaluator.evaluate(x + h);
    double f_minus = evaluator.evaluate(x - h);
    return (f_plus - f_minus) / (2 * h);
}

double NumericalCalculus::calculateIntegral(MathEvaluator& evaluator, double a, double b, int n) {
    // Simpson's 1/3 Rule
    // n harus genap
    if (n % 2 != 0) n++;
    
    double h = (b - a) / n;
    double sum = evaluator.evaluate(a) + evaluator.evaluate(b);
    
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0) {
            sum += 2 * evaluator.evaluate(x);
        } else {
            sum += 4 * evaluator.evaluate(x);
        }
    }
    
    return sum * h / 3.0;
}

void Plotter3D::plotToConsole() {
    if (points.empty()) return;
    
    cout << "\n========== GRAFIK 3D ==========\n";
    cout << "Fungsi: f(x,y) = " << functionName << "\n";
    cout << "Resolusi: " << resolution << "x" << resolution << "\n";
    cout << "Jumlah vertices: " << points.size() << "\n\n";
    
    // Find min/max z
    double minZ = points[0].z, maxZ = points[0].z;
    for (const auto& p : points) {
        minZ = min(minZ, p.z);
        maxZ = max(maxZ, p.z);
    }
    
    cout << "Range Z: [" << minZ << ", " << maxZ << "]\n";
    
    // Tampilkan beberapa titik
    cout << "\nBeberapa titik pada surface:\n";
    cout << "    x    |    y    |    z    \n";
    cout << "---------|---------|----------\n";
    
    int step = max(1, (int)(points.size() / 15));
    for (size_t i = 0; i < points.size(); i += step) {
        printf("%8.2f | %8.2f | %8.2f\n", points[i].x, points[i].y, points[i].z);
    }
}

// ============================================
// UTILITY FUNCTIONS
// ============================================

Color HSLtoRGB(double h, double s, double l) {
    Color rgb;
    
    auto hue2rgb = [](double p, double q, double t) {
        if (t < 0) t += 1;
        if (t > 1) t -= 1;
        if (t < 1.0/6.0) return p + (q - p) * 6 * t;
        if (t < 1.0/2.0) return q;
        if (t < 2.0/3.0) return p + (q - p) * (2.0/3.0 - t) * 6;
        return p;
    };
    
    if (s == 0) {
        rgb.r = rgb.g = rgb.b = l;
    } else {
        double q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        double p = 2 * l - q;
        rgb.r = hue2rgb(p, q, h + 1.0/3.0);
        rgb.g = hue2rgb(p, q, h);
        rgb.b = hue2rgb(p, q, h - 1.0/3.0);
    }
    
    return rgb;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayMenu() {
    cout << "\n";
    cout << "\n";
    cout << "   VISUALISASI FUNGSI 2D & 3D - KALKULUS 2  \n";
    cout << "--------------------------------------------\n";
    cout << "\nPilih Mode:\n";
    cout << "1. Fungsi 2D (1 variabel bebas)\n";
    cout << "2. Fungsi 3D (2 variabel bebas)\n";
    cout << "3. Mode Kalkulus (Diferensial & Integral)\n";
    cout << "4. Keluar\n";
    cout << "\nPilihan Anda: ";
}