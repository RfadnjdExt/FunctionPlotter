#ifndef FUNCTION_PLOTTER_H
#define FUNCTION_PLOTTER_H

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <fstream>

// Define mathematical constants
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#ifndef M_E
    #define M_E 2.71828182845904523536
#endif

using namespace std;

// Struct untuk titik 2D
struct Point2D {
    double x;
    double y;
};

// Struct untuk titik 3D
struct Point3D {
    double x;
    double y;
    double z;
};

// Struct untuk range
struct Range {
    double min;
    double max;
    double step;
};

// Struct untuk warna RGB
struct Color {
    double r, g, b;
};

// Class untuk evaluasi fungsi matematika
class MathEvaluator {
private:
    string expression;
    
    // Fungsi helper untuk parsing
    double parseNumber(const string& str, size_t& pos);
    double parseFactor(const string& str, size_t& pos, double x, double y = 0);
    double parseTerm(const string& str, size_t& pos, double x, double y = 0);
    double parseExpression(const string& str, size_t& pos, double x, double y = 0);
    
public:
    MathEvaluator(string expr);
    double evaluate(double x);
    double evaluate(double x, double y);
};

// Class untuk plotting 2D
class Plotter2D {
private:
    vector<Point2D> points;
    string functionName;
    
public:
    Plotter2D(string funcName);
    void addPoint(double x, double y);
    void generateData(MathEvaluator& evaluator, Range range);
    void plotToSVG(const string& filename);
    void plotToConsole();
};

// Class untuk plotting 3D
class Plotter3D {
private:
    vector<Point3D> points;
    string functionName;
    int resolution;
    
public:
    Plotter3D(string funcName, int res = 50);
    void generateSurface(MathEvaluator& evaluator, Range range);
    void exportToOBJ(const string& filename);
    void exportToPLY(const string& filename);
    void plotToConsole();
};

// Class untuk kalkulus numerik
class NumericalCalculus {
public:
    static double calculateDerivative(MathEvaluator& evaluator, double x, double h = 0.0001);
    static double calculateIntegral(MathEvaluator& evaluator, double a, double b, int n = 1000);
};

// Fungsi utility
Color HSLtoRGB(double h, double s, double l);
void clearScreen();
void displayMenu();

#endif