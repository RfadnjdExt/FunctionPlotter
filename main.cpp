#include "FunctionPlotter.h"

int main() {
    int choice;
    
    do {
        clearScreen();
        displayMenu();
        cin >> choice;
        cin.ignore();
        
        if (choice == 1) {
            // MODE 2D
            string function;
            Range range;
            
            cout << "\n========== MODE 2D ==========\n";
            cout << "Masukkan fungsi f(x): ";
            getline(cin, function);
            
            cout << "Range minimum: ";
            cin >> range.min;
            cout << "Range maximum: ";
            cin >> range.max;
            cout << "Step: ";
            cin >> range.step;
            
            try {
                MathEvaluator evaluator(function);
                Plotter2D plotter(function);
                
                cout << "\nMenghasilkan data...\n";
                plotter.generateData(evaluator, range);
                
                plotter.plotToConsole();
                plotter.plotToSVG("output_2d.svg");
                
                cout << "\n Grafik berhasil dibuat!\n";
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
            
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
        else if (choice == 2) {
            // MODE 3D
            string function;
            Range range;
            int resolution;
            
            cout << "\n========== MODE 3D ==========\n";
            cout << "Masukkan fungsi f(x,y): ";
            getline(cin, function);
            
            cout << "Range minimum: ";
            cin >> range.min;
            cout << "Range maximum: ";
            cin >> range.max;
            cout << "Resolusi (10-100): ";
            cin >> resolution;
            
            try {
                MathEvaluator evaluator(function);
                Plotter3D plotter(function, resolution);
                
                cout << "\nMenghasilkan surface...\n";
                plotter.generateSurface(evaluator, range);
                
                plotter.plotToConsole();
                plotter.exportToOBJ("output_3d.obj");
                
                cout << "\n Model 3D berhasil dibuat!\n";
                cout << "  File OBJ dapat dibuka dengan Blender/MeshLab\n";
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
            
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
        else if (choice == 3) {
            // MODE KALKULUS
            string function;
            int subChoice;
            
            cout << "\n========== MODE KALKULUS ==========\n";
            cout << "Masukkan fungsi f(x): ";
            getline(cin, function);
            
            try {
                MathEvaluator evaluator(function);
                
                cout << "\nPilih Operasi:\n";
                cout << "1. Hitung Turunan (Diferensial)\n";
                cout << "2. Hitung Integral Tentu\n";
                cout << "Pilihan: ";
                cin >> subChoice;
                
                if (subChoice == 1) {
                    double x;
                    cout << "Masukkan titik x: ";
                    cin >> x;
                    
                    double result = NumericalCalculus::calculateDerivative(evaluator, x);
                    cout << "\nHasil Diferensial f'(" << x << ") = " << result << endl;
                }
                else if (subChoice == 2) {
                    double a, b;
                    cout << "Masukkan batas bawah (a): ";
                    cin >> a;
                    cout << "Masukkan batas atas (b): ";
                    cin >> b;
                    
                    double result = NumericalCalculus::calculateIntegral(evaluator, a, b);
                    cout << "\nHasil Integral [" << a << ", " << b << "] = " << result << endl;
                }
                else {
                    cout << "Pilihan tidak valid!\n";
                }
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
            
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 4);
    
    cout << "\nTerima kasih telah menggunakan program ini!\n";
    return 0;
}