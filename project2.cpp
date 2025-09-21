#include <iostream>
#include <fstream> // for file open and close
#include <cmath> // for ceil function
#include <iomanip> // for setprecision

using namespace std; // std default namespace

// function prototypes 
float matrix_power(int[], int, float); //defense matrix power
void load_dva(float&, float&); //load defense matrix
void load_dva(int&, float&); //load missiles

// TEMPLATE FUNCTION Micro missile power
template <typename T>
T single_missile_power(T missilePower)
{
    if (missilePower <= 15) {
        return missilePower * 3; //If the passed in argument is less than or equal to 15, then it will returns 3 times the argument.
    } else 
    {
        if (missilePower >15) {
        return missilePower * 5; //If the passed in argument is greater than 15, then the function will return 5 times the argument.
        }
    } 
    // this function will only take one parameter at a time, and the parameter could be of type int or float. The return type will match the type of the parameter.
    return missilePower; // default return statement
}


// main function
int main() {
    // 1. READ COMBAT INFORMATION
    ifstream combatFile("combat.txt");
    //check file fail
    if (combatFile.fail()) {
        cout << "combat.txt fail to open.\n";
        return 0;
    }
    
    int botCount;
    combatFile >> botCount;  // first line

    // Read bot damages (from second line)
    int botDamage[botCount];
    for (int i = 0; i < botCount && i < 5; i++) {
            combatFile >> botDamage[i];
        }
    
    float bossDamage; // a number to store the damage of the boss
    combatFile >> bossDamage;  // last value on second line
    
    int defaultMissiles; // a number to store the default number of missiles
    float defaultMatrix; // a number to store the default power of the defense matrix // will call the matrix_power function to get the matrixPowerRequired
    // Read third line values
    combatFile >> defaultMissiles >> defaultMatrix;

    //close file
    combatFile.close();
    
    
    // function calls
    float matrixPowerRequired = matrix_power(botDamage, botCount, bossDamage);
    load_dva(defaultMatrix, matrixPowerRequired);
    //matrixPowerRequired
    matrix_power(botDamage, botCount, bossDamage); // to get the matrixPowerRequired
    

    float missilePowerRequired = 0; // sum of all the values returned from the single_missile_power function by passing in either bot's power(int) or the boss power(float)
    load_dva(defaultMissiles, missilePowerRequired); // missilePowerRequired
    //use for loop to call singile nmissile power function
    for (int i = 0; i < botCount && i < 5; i++) {           
        missilePowerRequired += single_missile_power(botDamage[i]);
    }
    missilePowerRequired += single_missile_power(bossDamage);
    

    // 4. report
    ofstream reportFile("report.txt");
    if (reportFile.fail()) {
        cout << "report.txt fail to open\n";
        return 0;
    }
    reportFile << "D.Va's Combat Report\n";
    reportFile << "Combat with " << botCount << " enemy bots and one enemy boss with power " 
           << fixed << setprecision(2) << bossDamage << ".\n";
    reportFile << "Loaded mech with " << defaultMissiles << " micro missiles and the defense matrix with power " 
           << fixed << setprecision(2) << defaultMatrix << ".\n";
    reportFile << "Ready for combat!\n";

    reportFile.close(); // Close the file

    return 0;
}

// function definitions
//  Defense Matrix Power
        float matrix_power (int botDamage[], int botCount, float bossDamage) {
            float totalDamage = bossDamage; //start with the boss damage
    
            for (int i = 0; i < botCount; i++) {
                totalDamage += botDamage[i];
            }
            return totalDamage;
        }
        
        //function overloading
        //Load Defense Matrix
        void load_dva (float& defaultMatrix, float& matrixPowerRequired) {
            if (defaultMatrix < matrixPowerRequired) {
                defaultMatrix = matrixPowerRequired;
            } 
        }                
        //Load Micro Missiles
        void load_dva (int& defaultMissiles, float& missilePowerRequired) {
            int missilesNeeded = ceil(missilePowerRequired / 30.0); //Round up
            if (missilesNeeded > defaultMissiles) {
                defaultMissiles = missilesNeeded;
            }
        }             