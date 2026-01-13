#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class extract_email_ID_from_mails_class
{
private:
    int num = 0;
    char **emails = nullptr;
    int length_array[20];
    void growAndAllocation(int length)
    {
        length_array[num] = length;
        num++;
        char **temp = new char *[num];
        for (int i = 0; i < num; i++)
        {
            temp[i] = new char[length_array[i] + 1];
        }
        if (emails != nullptr)
        {
            for (int i = 0; i < num - 1; i++)
            {
                for (int j = 0; emails[i][j] != '\0'; j++)
                {
                    temp[i][j] = emails[i][j];
                }
                temp[i][length_array[i]] = '\0';
            }
        }
        if (emails != nullptr)
        {
            for (int i = 0; i < num - 1; i++)
            {
                delete[] emails[i];
            }
            delete[] emails;
        }
        emails = temp;
    }

    bool duplicate_check(const char message[])
    {
        for (int i = 0; i < num; i++)
        {
            int k = 0;
            bool flag = true;
            for (int j = 0; emails[i][j] != '\0'; j++)
            {
                if (message[k++] != emails[i][j])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                return true;
            }
        }
        return false;
    }

    void store(char messages[][2000], int index, int email_num)
    {
        int length = 0;
        for (int j = index; messages[email_num][j] != '\0' && messages[email_num][j] != ' '; j++)
        {
            length++;
        }
        char check[length + 1];
        for (int i = 0; i < length; i++)
        {
            check[i] = messages[email_num][index + i];
        }

        if (emails != nullptr)
        {
            bool flag = false;
            check[length] = '\0';
            flag = duplicate_check(check);
            if (flag)
                return;
        }

        growAndAllocation(length);
        int i = 0;
        for (int j = index; messages[email_num][j] != '\0' && messages[email_num][j] != ' '; j++)
        {
            emails[num - 1][i++] = messages[email_num][j];
        }
        emails[num - 1][i] = '\0';
    }

    void extract_emails(char messages[][2000], const int N)
    {

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; messages[i][j] != '\0'; j++)
            {
                if (messages[i][j] == '@')
                {
                    for (int k = j; k > 0; k--)
                    {
                        if (messages[i][k] == ' ' || k == 1)
                        {
                            if (k == 1)
                            {
                                store(messages, 0, i);
                            }
                            else
                                store(messages, k + 1, i);
                            break;
                        }
                    }
                }
            }
        }
    }

    void display()
    {
        for (int i = 0; i < num; i++)
        {
            cout << emails[i] << endl;
        }
        cout << endl;
    }

public:
    void extract_email_ID_from_mails()
    {

        char messages[100][2000];
        cout << "1. Enter you own mails for testing:" << endl;
        cout << "2. Want to test the default entered mails" << endl;
        int option = -1;
        int N = 4;
        while (option == -1)
        {
            cout << "Enter the option number: ";
            while (!(cin >> option))
            {
                cin.clear();
                cin.ignore(999999999, '\n');
            }
            cout << endl;
            if (option == 1)
            {
                cout << "Enter the number of mails for testing: ";
                cin >> N;
                cin.ignore();

                if (N > 100)
                {
                    cout << "Set the mails coutnt 100" << endl;
                    N = 100;
                }
                for (int i = 0; i < N; i++)
                {
                    cout << "Enter mail " << i + 1 << ": ";
                    cin.getline(messages[i], 2000);
                }
            }
            else if (option == 2)
            {

                strcpy(messages[0], "Please contact john.doe@company.com for HR-related queries.");
                strcpy(messages[1], "For technical issues, email tech.support@company.com or admin@company.com.");
                strcpy(messages[2], "john.doe@company.com is currently out of office.");
                strcpy(messages[3], "Send your reports to manager.hr@company.com by evening.");
                cout << "Emails:" << endl;
                for (int i = 0; i < N; i++)
                {
                    cout << messages[i] << endl;
                }
            }
            else
            {
                option = -1;
                cout << "Error! Invalid Option" << endl;
            }
        }
        extract_emails(messages, N);
        cout << "\nExtracted Email ID's: " << endl;
        display();

        for (int i = 0; i < num; i++)
        {
            delete[] emails[i];
        }
        delete[] emails;

        cout << "Details of this code:" << endl
             << "parsing of a static 2D char array of messages, extract all distinct email IDs (found around @), and store them in a resizable dynamic 2D array, where each row is exactly the email’s length + 1." << endl;
        cout << endl;
        return;
    }
};

class polynomial_calculation_class
{
private:
    // the output of sum is save in first polynomial(updated) and second remain same;
    // product will be between updated first polynomail and second polynomail and result will be in new polynomial;

    void sum(int *&exponent, int *exponent2, int *&coefficients, int *coefficients2, int &terms, const int terms2)
    {
        for (int i = 0; i < terms2; i++)
        {
            bool present = false;
            int j;
            for (j = 0; j < terms; j++)
            {
                if (exponent2[i] == exponent[i])
                {
                    coefficients[j] += coefficients2[i];
                    present = true;
                    break;
                }
            }
            if (!present)
            {

                int *tempexpo = new int[terms + 1];
                int *tempcoff = new int[terms + 1];
                for (int k = 0; k < terms; k++)
                {
                    tempexpo[k] = exponent[k];
                    tempcoff[k] = coefficients[k];
                }
                delete[] exponent;
                delete[] coefficients;
                tempexpo[terms] = exponent2[i];
                tempcoff[terms] = coefficients2[i];
                exponent = tempexpo;
                coefficients = tempcoff;
                terms++;
            }
        }
    }

    void product(int *&resultexpo, int *&resultcoff, int *exponent, int *exponent2, int *coefficients, int *coefficients2, int terms, int terms2)
    {
        int position_expo = 0;
        int position_coff = 0;
        for (int i = 0; i < terms; i++)
        {
            for (int j = 0; j < terms2; j++)
            {
                resultexpo[position_expo++] = exponent[i] + exponent2[j];
                resultcoff[position_coff++] = coefficients[i] * coefficients2[j];
            }
        }
    }

public:
    void polynomial_calculation()
    {
        int terms;
        cout << "Enter the number of terms in the polynomial 1: ";
        cin >> terms;
        int *coefficients = new int[terms];
        int *exponent = new int[terms];
        int positionexpo = 0;
        int positioncoff = 0;
        for (int i = 0; i < terms; i++)
        {
            int coff = 0;
            cout << "Enter the coefficient of term " << i + 1 << ": ";
            cin >> coff;
            int expo = 0;
            cout << "Enter the exponent of term " << i + 1 << ": ";
            cin >> expo;
            exponent[positionexpo++] = expo;
            coefficients[positioncoff++] = coff;
        }
        cout << "Before arranging and removing duplicates:" << endl;
        for (int i = 0; i < terms; i++)
        {
            if (exponent[i] == -1)
            {
                continue;
            }

            if (exponent[i] == 0)
            {
                cout << coefficients[i];
                if (i != 0)
                {
                    cout << " + ";
                }
                continue;
            }
            if (exponent[i] == 1)
            {
                cout << coefficients[i] << "x";
                if (i != terms - 1)
                {
                    cout << " + ";
                }
                continue;
            }
            cout << coefficients[i] << "x^" << exponent[i];
            if (i != terms - 1)
            {
                cout << " + ";
            }
        }
        // arranging
        for (int i = 0; i < terms; i++)
        {
            for (int j = i; j < terms; j++)
            {
                if (exponent[i] > exponent[j])
                {
                    int tempexpo = exponent[i];
                    exponent[i] = exponent[j];
                    exponent[j] = tempexpo;
                    int tempcoff = coefficients[i];
                    coefficients[i] = coefficients[j];
                    coefficients[j] = tempcoff;
                }
            }
        }

        // adding duplicates
        for (int i = 0; i < terms; i++)
        {
            for (int j = i + 1; j < terms; j++)
            {
                if (exponent[i] == exponent[j])
                {
                    coefficients[i] += coefficients[j];
                    exponent[j] = -1;
                    coefficients[j] = 0;
                }
            }
        }
        cout << endl
             << "After:" << endl;
        for (int i = terms - 1; i >= 0; i--)
        {
            if (exponent[i] == -1)
            {
                continue;
            }

            if (exponent[i] == 0)
            {
                cout << coefficients[i];
                continue;
            }
            if (exponent[i] == 1)
            {
                cout << coefficients[i] << "x";
                if (i != 0)
                {
                    cout << " + ";
                }
                continue;
            }
            cout << coefficients[i] << "x^" << exponent[i];
            if (i != 0)
            {
                cout << " + ";
            }
        }

        cout << endl
             << "Do you want to enter next polynomial(1/0): ";
        int option;
        while (!(cin >> option))
        {
            cin.clear();
            cin.ignore(999999999, '\n');
        }
        int terms2;
        int *coefficients2 = new int[terms2];
        int *exponent2 = new int[terms2];
        if (option == 1)
        {
            cout << endl
                 << "Enter the number of terms in the polynomial 2: ";
            cin >> terms2;
            int positionexpo2 = 0;
            int positioncoff2 = 0;
            for (int i = 0; i < terms2; i++)
            {
                int coff2 = 0;
                cout << "Enter the coefficient of term " << i + 1 << ": ";
                cin >> coff2;
                int expo2 = 0;
                cout << "Enter the exponent of term " << i + 1 << ": ";
                cin >> expo2;
                exponent2[positionexpo2++] = expo2;
                coefficients2[positioncoff2++] = coff2;
            }
            cout << "Before arranging and removing duplicates:" << endl;
            for (int i = 0; i < terms2; i++)
            {
                if (exponent2[i] == -1)
                {
                    continue;
                }

                if (exponent2[i] == 0)
                {
                    cout << coefficients2[i];
                    if (i != 0)
                    {
                        cout << " + ";
                    }
                    continue;
                }
                if (exponent2[i] == 1)
                {
                    cout << coefficients2[i] << "x";
                    if (i != terms2 - 1)
                    {
                        cout << " + ";
                    }
                    continue;
                }
                cout << coefficients2[i] << "x^" << exponent2[i];
                if (i != terms2 - 1)
                {
                    cout << " + ";
                }
            }
            // arranging
            for (int i = 0; i < terms2; i++)
            {
                for (int j = i; j < terms2; j++)
                {
                    if (exponent2[i] > exponent2[j])
                    {
                        int tempexpo2 = exponent2[i];
                        exponent2[i] = exponent2[j];
                        exponent2[j] = tempexpo2;
                        int tempcoff2 = coefficients2[i];
                        coefficients2[i] = coefficients2[j];
                        coefficients2[j] = tempcoff2;
                    }
                }
            }

            // adding duplicates
            for (int i = 0; i < terms2; i++)
            {
                for (int j = i + 1; j < terms2; j++)
                {
                    if (exponent2[i] == exponent2[j])
                    {
                        coefficients2[i] += coefficients2[j];
                        exponent2[j] = -1;
                        coefficients2[j] = 0;
                    }
                }
            }
            cout << endl
                 << "After:" << endl;
            for (int i = terms2 - 1; i >= 0; i--)
            {
                if (exponent2[i] == -1)
                {
                    continue;
                }

                if (exponent2[i] == 0)
                {
                    cout << coefficients2[i];
                    continue;
                }
                if (exponent2[i] == 1)
                {
                    cout << coefficients2[i] << "x";
                    if (i != 0)
                    {
                        cout << " + ";
                    }
                    continue;
                }
                cout << coefficients2[i] << "x^" << exponent2[i];
                if (i != 0)
                {
                    cout << " + ";
                }
            }
        }
        else
        {
            cout << "Details of this code: "
                 << "a polynomial calculator in C++ using only dynamic arrays (no structs/classes). The program should support input (unique exponents, sorted), output in standard form, addition, and multiplication of polynomials, while ensuring proper dynamic allocation" << endl;
            return;
        }
        cout << endl
             << "1. Sum" << endl
             << "2. Product" << endl;
        int option2;
        cout << "Enter the option number(or any button to exit): ";
        while (!(cin >> option2))
        {
            cin.clear();
            cin.ignore(999999999, '\n');
        }
        if (option2 == 1)
        {
            sum(exponent, exponent2, coefficients, coefficients2, terms, terms2);
            cout << endl
                 << "After SUM:" << endl;

            // arranging
            for (int i = 0; i < terms; i++)
            {
                for (int j = i; j < terms; j++)
                {
                    if (exponent[i] > exponent[j])
                    {
                        int tempexpo = exponent[i];
                        exponent[i] = exponent[j];
                        exponent[j] = tempexpo;
                        int tempcoff = coefficients[i];
                        coefficients[i] = coefficients[j];
                        coefficients[j] = tempcoff;
                    }
                }
            }

            // adding duplicates
            for (int i = 0; i < terms; i++)
            {
                for (int j = i + 1; j < terms; j++)
                {
                    if (exponent[i] == exponent[j])
                    {
                        coefficients[i] += coefficients[j];
                        exponent[j] = -1;
                        coefficients[j] = 0;
                    }
                }
            }
            for (int i = terms - 1; i >= 0; i--)
            {
                if (exponent[i] == -1)
                {
                    continue;
                }

                if (exponent[i] == 0)
                {
                    cout << coefficients[i];
                    continue;
                }
                if (exponent[i] == 1)
                {
                    cout << coefficients[i] << "x";
                    if (i != 0)
                    {
                        cout << " + ";
                    }
                    continue;
                }
                cout << coefficients[i] << "x^" << exponent[i];
                if (i != 0)
                {
                    cout << " + ";
                }
            }
        }
        else if (option2 == 2)
        {
            int *resultexpo = new int[terms * terms2];
            int *resultcoff = new int[terms * terms2];
            product(resultexpo, resultcoff, exponent, exponent2, coefficients, coefficients2, terms, terms2);
            cout << endl
                 << "AFTER PRODUCT: " << endl;

            // arranging
            int resultTerms = terms * terms2;
            for (int i = 0; i < resultTerms; i++)
            {
                for (int j = i; j < resultTerms; j++)
                {
                    if (resultexpo[i] > resultexpo[j])
                    {
                        int tempexpo = resultexpo[i];
                        resultexpo[i] = resultexpo[j];
                        resultexpo[j] = tempexpo;
                        int tempcoff = resultcoff[i];
                        resultcoff[i] = resultcoff[j];
                        resultcoff[j] = tempcoff;
                    }
                }
            }

            // adding duplicates
            for (int i = 0; i < resultTerms; i++)
            {
                for (int j = i + 1; j < resultTerms; j++)
                {
                    if (resultexpo[i] == resultexpo[j])
                    {
                        resultcoff[i] += resultcoff[j];
                        resultexpo[j] = -1;
                        resultcoff[j] = 0;
                    }
                }
            }
            for (int i = resultTerms - 1; i >= 0; i--)
            {
                if (resultexpo[i] == -1)
                {
                    continue;
                }
                if (resultcoff[i] == 0)
                {
                    continue;
                }
                if (resultexpo[i] == 0)
                {
                    cout << resultcoff[i];
                    continue;
                }
                if (resultexpo[i] == 1)
                {
                    cout << resultcoff[i] << "x";
                    if (i != 0)
                    {
                        cout << " + ";
                    }
                    continue;
                }
                cout << resultcoff[i] << "x^" << resultexpo[i];
                if (i != 0)
                {
                    cout << " + ";
                }
            }
        }
        else
        {
            cout << "OK so we move next" << endl;
        }
        cout << endl;

        cout << "\nDetails of this code: " << endl;
        cout << "a polynomial calculator in C++ using only dynamic arrays (no structs/classes). The program should support input (unique exponents, sorted), output in standard form, addition, and multiplication of polynomials, while ensuring proper dynamic allocation" << endl;
        return;
    }
};

// 3D vectors code starts here
class VectorType
{
private:
    double *x;
    double *y;
    double *z;

public:
    VectorType(double x = 0, double y = 0, double z = 0)
    {
        this->x = new double(x);
        this->y = new double(y);
        this->z = new double(z);
    }
    VectorType(const VectorType &obj)
    {
        this->x = new double(*obj.x);
        this->y = new double(*obj.y);
        this->z = new double(*obj.z);
    }
    ~VectorType()
    {
        delete x;
        delete y;
        delete z;
    }
    VectorType &operator=(const VectorType &obj)
    {
        if (this == &obj)
            return *this;
        this->x = new double(*obj.x);
        this->y = new double(*obj.y);
        this->z = new double(*obj.z);
        return *this;
    }
    double operator*(const VectorType &obj)
    {
        double temp = 0.0;
        temp += (*this->x) * (*obj.x);
        temp += (*this->y) * (*obj.y);
        temp += (*this->z) * (*obj.z);
        return temp;
    }
    double length()
    {
        double total = 0;
        total += (*x * *x);
        total += (*y * *y);
        total += (*z * *z);
        total = sqrt(total);
        return total;
    }
    double angle(VectorType &obj)
    {
        double product = *this * obj;
        double a = this->length();
        double b = obj.length();
        ;
        double c = a * b;
        product = product / c;
        double result = acos(product);
        return result;
    }
    VectorType operator+(VectorType &obj)
    {
        VectorType temp;
        *temp.x = *this->x + *obj.x;
        *temp.y = *this->y + *obj.y;
        *temp.z = *this->z + *obj.z;
        return temp;
    }
    VectorType operator-(VectorType &obj)
    {
        VectorType temp;
        *temp.x = *this->x - *obj.x;
        *temp.y = *this->y - *obj.y;
        *temp.z = *this->z - *obj.z;
        return temp;
    }
    VectorType &operator++()
    {

        (*this->x)++;
        (*this->y)++;
        (*this->z)++;
        return *this;
    }

    VectorType &operator--()
    {
        (*this->x)--;
        (*this->y)--;
        (*this->z)--;
        return *this;
    }

    VectorType operator++(int)
    {
        VectorType temp = *this;
        (*this->x)++;
        (*this->y)++;
        (*this->z)++;
        return temp;
    }
    VectorType operator--(int)
    {
        VectorType temp = *this;
        (*this->x)--;
        (*this->y)--;
        (*this->z)--;
        return temp;
    }

    friend bool operator==(const VectorType &obj1, const VectorType &obj2);
    friend bool operator!=(const VectorType &obj1, const VectorType &obj2);
    friend ostream &operator<<(ostream &out, const VectorType &obj);
    friend istream &operator>>(istream &in, VectorType &obj);
};
bool operator==(const VectorType &obj1, const VectorType &obj2)
{
    return (*(obj1.x) == *(obj2.x) &&
            *(obj1.y) == *(obj2.y) &&
            *(obj1.z) == *(obj2.z));
}

bool operator!=(const VectorType &obj1, const VectorType &obj2)
{
    return (*obj1.x != *obj2.x || *obj1.y != *obj2.y || *obj1.z != *obj2.z);
}
ostream &operator<<(ostream &out, const VectorType &obj)
{
    out << *obj.x << "x +" << *obj.y << "y +" << *obj.z << "z" << endl;
    return out;
}
istream &operator>>(istream &in, VectorType &obj)
{
    cout << "Enter the values(x,y,z)" << endl;
    in >> *obj.x >> *obj.y >> *obj.z;
    return in;
}

void vectors_3D()
{
    VectorType v, u;
    cout << "Enter the components of u: " << endl;
    cin >> u;
    cout << "Enter the components of v: " << endl;
    cin >> v;
    cout << "Vector u:" << endl;
    cout << u;
    cout << "Vector v:" << endl;
    cout << v;
    VectorType w = u;
    cout << "Copied vector w from u:" << endl;
    cout << w;
    bool flag = true;
    do
    {
        flag = true;
        cout << "Options:" << endl;
        cout << "1. pre_increment" << endl
             << "2. post_increment" << endl
             << "3. Equality check" << endl
             << "4. Product" << endl
             << "5. Sum" << endl
             << "6. Difference" << endl
             << "7. Length" << endl
             << "8. Angle" << endl;
        int opt1;
        cout << "Enter option number for vector u: ";
        while (!(cin >> opt1))
        {
            cin.clear();
            cin.ignore(999999999, '\n');
        }
        if (opt1 == 1)
        {
            cout << "pre_increment: ";
            cout << (++u) << endl;
        }
        else if (opt1 == 2)
        {
            cout << "post_increment: ";
            cout << (u++) << endl;
        }
        else if (opt1 == 3)
        {

            if (u == v)
            {
                cout << "Equal" << endl;
            }
            else if (u != v)
            {
                cout << "Not equal" << endl;
            }
        }
        else if (opt1 == 4)
        {
            int num = v * u;
            cout << num << endl;
        }
        else if (opt1 == 5)
        {
            cout << u + v << endl;
        }

        else if (opt1 == 6)
        {
            cout << u - v << endl;
        }
        else if (opt1 == 7)
        {
            cout << "length: ";
            cout << v.length() << endl;
        }
        else if (opt1 == 8)
        {
            cout << "Angle: ";
            cout << v.angle(u) << endl;
        }
        cout << "Do you want to check another manipulation of u and v(0/1): ";
        int opt;
        while (!(cin >> opt))
        {
            cin.clear();
            cin.ignore(999999999, '\n');
        }
        if (opt == 0)
            flag = false;
    } while (flag);
    cout << endl
         << "Details of this code:" << endl
         << "VectorType class that represents 3D vectors using dynamic memory. It supports constructors, destructor, assignment, and overloaded operators for vector math (dot product, length, angle, add/subtract, ++/--, comparisons, input/output)." << endl;
    return;
}
// 3D vectors code ends here

// String code starts here
class myString
{
    char *str;
    int length;

public:
    myString(const char *mystr = "")
    {
        int i = 0;
        while (mystr[i] != '\0')
        {
            i++;
        }
        length = i;
        str = new char[length + 1];
        for (int i = 0; i < length; i++)
            str[i] = mystr[i];
        str[length] = '\0';
    }
    myString(const myString &other)
    {
        length = other.length;
        str = new char[length + 1];
        for (int i = 0; i <= length; i++)
        {
            str[i] = other.str[i];
        }
    }
    ~myString()
    {
        delete[] str;
    }
    int Length()
    {
        return length;
    }
    char *uppercase()
    {
        char *mystr = new char[length + 1];
        for (int i = 0; i < length; i++)
        {
            if (str[i] >= 'a' && str[i] <= 'z')
            {
                mystr[i] = str[i] - 32;
            }
            else
            {
                mystr[i] = str[i];
            }
        }
        mystr[length] = '\0';
        return mystr;
    }
    char *lowercase()
    {
        char *mystr = new char[length + 1];
        for (int i = 0; i < length; i++)
        {
            if (str[i] >= 65 && str[i] <= 90)
            {
                mystr[i] = str[i] + 32;
            }
            else
            {
                mystr[i] = str[i];
            }
        }
        mystr[length] = '\0';
        return mystr;
    }
    char at(int n) { return str[n]; }

    char *substring(int s, int e)
    {
        char *temp = new char[e - s + 1];
        int k = 0;
        for (int i = s; i < e; i++)
        {
            temp[k++] = str[i];
        }
        temp[k] = '\0';
        return temp;
    }

    const char &operator[](int n) const
    {
        return str[n];
    }

    // int index(const char *substr)
    // {
    //     int i;
    //     for (i = 0; str[i] != '\0'; i++)
    //     {
    //         if (str[i] != substr[0])
    //         {
    //             continue;
    //         }
    //         bool flag = false;
    //         for (int j = 0; substr[j] != '\0'; j++)
    //         {
    //             if (str[j + i] != substr[j])
    //             {
    //                 flag = false;
    //                 break;
    //             }
    //             flag = true;
    //         }
    //         if (flag)
    //             break;
    //     }
    //     return i;
    // }

    int index(const char *substr)
    {
        int sublen = 0;
        while (substr[sublen] != '\0')
            sublen++;

        for (int i = 0; str[i] != '\0'; i++)
        {
            if (str[i] == substr[0])
            {
                bool found = true;
                for (int j = 0; j < sublen; j++)
                {
                    if (str[i + j] != substr[j])
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                    return i;
            }
        }
        return -1; // Return -1 if not found
    }

    bool compare(const myString &mystr)
    {
        int l1 = mystr.length;
        int l2 = length;
        if (l1 != l2)
            return false;
        bool flag = false;
        for (int i = 0; str[i] != '\0'; i++)
        {
            if (str[i] != mystr.str[i])
            {
                flag = false;
                break;
            }
            flag = true;
        }
        return flag;
    }

    void append(const myString &mystr)
    {
        int l1 = length;
        int l2 = mystr.length;
        char *newstr = new char[l1 + l2 + 2];
        for (int i = 0; i < l1; i++)
        {
            newstr[i] = this->str[i];
        }
        newstr[l1] = ' ';
        for (int i = 0; i < l2; i++)
        {
            newstr[i + l1 + 1] = mystr.str[i];
        }
        newstr[l1 + l2 + 1] = '\0';
        delete[] this->str;
        this->str = newstr;
        this->length = l1 + l2 + 1;
    }
    void append(const char *mystr)
    {
        int l1 = length;
        int l2 = 0;
        while (mystr[l2] != '\0')
        {
            l2++;
        }
        char *newstr = new char[l1 + l2 + 2];
        for (int i = 0; i < l1; i++)
        {
            newstr[i] = this->str[i];
        }
        newstr[l1] = ' ';
        for (int i = 0; i < l2; i++)
        {
            newstr[i + l1 + 1] = mystr[i];
        }
        newstr[l1 + l2 + 1] = '\0';
        delete[] this->str;
        this->str = newstr;
        this->length = l1 + l2 + 1;
    }

    void append(const char mychr)
    {
        int l1 = length;
        char *newstr = new char[l1 + 3];
        for (int i = 0; i < l1; i++)
        {
            newstr[i] = this->str[i];
        }
        newstr[l1] = mychr;
        newstr[l1 + 1] = ' ';
        newstr[l1 + 2] = '\0';
        delete[] this->str;
        this->str = newstr;
        this->length = l1 + 2;
    }
    void append(int num)
    {
        char buffer[20];
        sprintf(buffer, "%d", num);
        append(buffer);
    }

    void append(float num)
    {
        char buffer[20];
        sprintf(buffer, "%.2f", num);
        append(buffer);
    }

    void prepend(const myString &mystr)
    {
        int l1 = length;
        int l2 = mystr.length;
        char *newstr = new char[l1 + l2 + 2];
        for (int i = 0; i < l1; i++)
        {
            newstr[i] = mystr.str[i];
        }
        newstr[l1] = ' ';
        for (int i = 0; i < l2; i++)
        {
            newstr[i + l1 + 1] = this->str[i];
        }
        newstr[l1 + l2 + 1] = '\0';
        delete[] this->str;
        this->str = newstr;
        this->length = l1 + l2 + 1;
    }
    void prepend(const char *mystr)
    {
        int l1 = length;
        int l2 = 0;
        while (mystr[l2] != '\0')
        {
            l2++;
        }
        char *newstr = new char[l1 + l2 + 2];
        for (int i = 0; i < l2; i++)
        {
            newstr[i] = mystr[i];
        }
        newstr[l2] = ' ';
        for (int i = 0; i < l1; i++)
        {
            newstr[i + l2 + 1] = this->str[i];
        }
        newstr[l1 + l2 + 1] = '\0';
        delete[] this->str;
        this->str = newstr;
        this->length = l1 + l2 + 1;
    }

    void prepend(const char mychr)
    {
        int l1 = length;
        char *newstr = new char[l1 + 3];
        newstr[0] = mychr;
        newstr[1] = ' ';
        for (int i = 0; i < l1; i++)
        {
            newstr[i + 2] = this->str[i];
        }
        newstr[l1 + 2] = '\0';
        delete[] this->str;
        this->str = newstr;
        this->length = l1 + 2;
    }
    void prepend(int num)
    {
        char buffer[20];
        sprintf(buffer, "%d", num);
        prepend(buffer);
    }

    void prepend(float num)
    {
        char buffer[20];
        sprintf(buffer, "%.2f", num);
        prepend(buffer);
    }

    myString operator+(const myString &mystr)
    {
        myString temp = *this;
        temp.append(mystr);
        return temp;
    }
    myString operator+(const char *mystr)
    {
        myString temp = *this;
        temp.append(mystr);
        return temp;
    }
    friend myString operator+(const char *mystr1, myString &mystr2); // if "heloo"+s1

    myString &operator=(const myString &mystr)
    {
        if (this != &mystr)
        {
            delete[] str;
            length = mystr.length;
            str = new char[length + 1];
            for (int i = 0; i <= length; i++)
                str[i] = mystr.str[i];
        }
        return *this;
    }
    bool operator==(const myString &mystr)
    {
        if (this->length != mystr.length)
            return false;
        for (int i = 0; i < length; ++i)
        {
            if (str[i] != mystr.str[i])
                return false;
        }
        return true;
    }

    bool operator!=(const myString &mystr)
    {
        return !(*this == mystr);
    }

    bool operator>(const myString &mystr)
    {
        if (this->length > mystr.length)
        {
            for (int i = 0; i < length; ++i)
            {
                if (str[i] < mystr.str[i])
                    return false;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator<(const myString &mystr)
    {
        if (this->length < mystr.length)
        {
            for (int i = 0; i < length; ++i)
            {
                if (str[i] > mystr.str[i])
                    return false;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    char operator[](int i)
    {
        return this->str[i];
    }
    const char *getStr() const { return str; }

    friend ostream &operator<<(ostream &out, const myString &mystr);
    friend istream &operator>>(istream &in, myString &mystr);
};
myString operator+(const char *mystr1, const myString &mystr2)
{ // if "heloo"+s1
    myString temp = mystr2;
    temp.prepend(mystr1);
    return temp;
}

ostream &operator<<(ostream &out, const myString &mystr)
{
    out << mystr.str << endl;
    return out;
}
istream &operator>>(istream &in, myString &mystr)
{
    cout << "enter the string: " << endl;
    char *buffer = new char[300];
    in.getline(buffer, 300);
    int size = 0;
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        size++;
    }
    delete[] mystr.str;
    mystr.length = size;
    mystr.str = new char[mystr.length + 1];
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        mystr.str[i] = buffer[i];
    }
    mystr.str[mystr.length] = '\0';
    return in;
}

void my_string()
{
    cin.ignore(1000, '\n');
    myString s1;
    cin >> s1;
    cout << "You entered string1: " << s1;
    myString s2;
    cin >> s2;
    cout << "You entered string2: " << s2;

    bool flag = true;
    do
    {
        flag = true;
        cout << "Options:" << endl;
        cout << "1. s1+s2" << endl
             << "2. appending(s1+s2, int, float, char)" << endl
             << "3. prepending(s1+s2, int, float, char)" << endl
             << "4. Uppercase" << endl
             << "5. Lowercase" << endl
             << "6. []/index number" << endl
             << "7. substring[from,to]" << endl
             << "8. find index of entered substring" << endl
             << "9. comparison" << endl
             << "10. copying" << endl;
        int opt1;
        cout << "Enter option number: ";
        while (!(cin >> opt1))
        {
            cin.clear();
            cin.ignore(999999999, '\n');
        }
        if (opt1 == 1)
        {
            // // Test + operator
            myString s3 = s1 + s2;
            cout << "s1 + s2: " << s3;
        }
        else if (opt1 == 2)
        {
            myString s4 = s1 + s2;
            cout << "After s1+s2: " << s4;
            s4.append(123);
            cout << "After appending 123: " << s4;
            s4.append(4.56f);
            cout << "After appending 4.56: " << s4;
            s4.append('!');
            cout << "After appending character !: " << s4;
        }
        else if (opt1 == 3)
        {
            // // Test prepend (int, float, char)
            myString s5 = s1 + s2;
            cout << "After s1+s2: " << s5;
            s5.prepend(123);
            cout << "After prepending 123: " << s5;
            s5.prepend(4.56f);
            cout << "After appending 4.56: " << s5;
            s5.prepend('!');
            cout << "After appending character !: " << s5;
        }
        else if (opt1 == 4)
        {
            cout << "Uppercase s1: " << s1.uppercase() << endl;
        }
        else if (opt1 == 5)
        {
            cout << "Lowercase s2: " << s2.lowercase() << endl;
        }

        else if (opt1 == 6)
        {
            cout << "s2[1]: " << s2[1] << endl;
            cout << "s2.at(2): " << s2.at(2) << endl;
        }
        else if (opt1 == 7)
        {
            // // Test substring
            char *sub = s1.substring(1, 4);
            cout << "Substring s1(1,4): " << sub << endl;
            delete[] sub;
        }
        else if (opt1 == 8)
        {
            cout << "enter the valid substring to find the index in s1: ";
            char buffer[100];
            cin >> buffer;
            cout << "Index of substring in s1: " << s1.index(buffer) << endl;
        }
        else if (opt1 == 9)
        {
            cout << "s2 == s2: " << (s2 == s2) << endl;
            cout << "s1 != s2: " << (s1 != s2) << endl;
        }
        else if (opt1 == 10)
        {
            myString s4;
            s4 = s2;
            cout << "s4 = s2: " << s4;
        }
        cout << "Do you want to check another manipulation(0/1): ";
        int opt;
        while (!(cin >> opt))
        {
            cin.clear();
            cin.ignore(999999999, '\n');
        }
        if (opt == 0)
            flag = false;
    } while (flag);
    cout << endl
         << "Details of this code:" << endl
         << "a custom MyString class in C++ using dynamic memory that mimics standard string behavior. It supports operations like length, case conversion, substring, search, compare, concat/prepend, and also overloads operators (+, =, ==, !=, <, >, [], <<, >>) for flexible string handling." << endl;
    return;
}

// String code ends here

// roman language starts here
class Roman
{
    string roman;
    int length;
    int value;
    void toInteger();
    int getvalue(const char c);

public:
    Roman(const string roman = "") : roman(roman), length(roman.length()), value(0)
    {
        toInteger();
    }
    int getInteger()
    {
        return value;
    }

    string toRoman(int num)
    {
        int temp = num;
        string newroman = "";
        while (temp > 0)
        {
            if (temp >= 1000)
            {
                newroman += "M";
                temp -= 1000;
            }
            else if (temp >= 900)
            {
                newroman += "CM";
                temp -= 900;
            }
            else if (temp >= 500)
            {
                newroman += "D";
                temp -= 500;
            }
            else if (temp >= 400)
            {
                newroman += "CD";
                temp -= 400;
            }
            else if (temp >= 100)
            {
                newroman += "C";
                temp -= 100;
            }
            else if (temp >= 90)
            {
                newroman += "XC";
                temp -= 90;
            }
            else if (temp >= 50)
            {
                newroman += "L";
                temp -= 50;
            }
            else if (temp >= 40)
            {
                newroman += "XL";
                temp -= 40;
            }
            else if (temp >= 10)
            {
                newroman += "X";
                temp -= 10;
            }
            else if (temp >= 9)
            {
                newroman += "IX";
                temp -= 9;
            }
            else if (temp >= 5)
            {
                newroman += "V";
                temp -= 5;
            }
            else if (temp >= 4)
            {
                newroman += "IV";
                temp -= 4;
            }
            else
            {
                newroman += "I";
                temp -= 1;
            }
        }
        return newroman;
    }
    string getstring()
    {
        return roman;
    }

    Roman operator+(const Roman &rm)
    {
        int total = this->value + rm.value;
        string result = toRoman(total);
        Roman temp(result);
        return temp;
    }
    Roman operator*(const Roman &rm)
    {
        int total = this->value * rm.value;
        string result = toRoman(total);
        Roman temp(result);
        return temp;
    }

    Roman operator/(const Roman &rm)
    {
        int total = this->value / rm.value;
        string result = toRoman(total);
        Roman temp(result);
        return temp;
    }
    bool operator==(const Roman &rm)
    {
        if (this->value == rm.value)
            return true;
        else
            return false;
    }

    bool operator!=(const Roman &rm)
    {
        if (this->value != rm.value)
            return true;
        else
            return false;
    }

    bool operator>(const Roman &rm)
    {
        if (this->value > rm.value)
            return true;
        else
            return false;
    }

    bool operator<(const Roman &rm)
    {
        if (this->value < rm.value)
            return true;
        else
            return false;
    }

    Roman operator-(const Roman &rm)
    {
        int total = this->value - rm.value;
        if (total <= 0)
        {
            cout << "Roman do no deal in values less than 0" << endl;
            string result = "Error";
            Roman temp(result);
            return temp;
        }
        string result = toRoman(total);
        Roman temp(result);
        return temp;
    }

    Roman operator++()
    {
        this->value += 1;
        string result = toRoman(value);
        this->roman = result;
        return *this;
    }

    Roman operator--()
    {
        this->value -= 1;
        string result = toRoman(value);
        this->roman = result;
        return *this;
    }

    Roman operator++(int)
    {
        Roman temp = *this;
        this->value += 1;
        string result = toRoman(value);
        this->roman = result;
        return temp;
    }

    Roman operator--(int)
    {
        Roman temp = *this;
        this->value -= 1;
        string result = toRoman(value);
        this->roman = result;
        return temp;
    }

    friend ostream &operator<<(ostream &out, const Roman &rm);
};

ostream &operator<<(ostream &out, const Roman &rm)
{
    for (int i = 0; rm.roman[i] != '\0'; i++)
    {
        out << rm.roman[i];
    }
    return out;
}

void Roman::toInteger()
{
    if (length == 0)
        return;
    value += getvalue(roman[length - 1]);
    for (int i = length - 2; i >= 0; i--)
    {
        int curr = getvalue(roman[i]);
        int prev = getvalue(roman[i + 1]);

        if (curr >= prev)
        {

            value += curr;
        }
        else if (curr < prev)
            value -= curr;
    }
}

int Roman::getvalue(const char c)
{
    if (c == 'I')
    {
        return 1;
    }
    else if (c == 'V')
    {
        return 5;
    }
    else if (c == 'X')
    {
        return 10;
    }
    else if (c == 'L')
    {
        return 50;
    }
    else if (c == 'C')
    {
        return 100;
    }
    else if (c == 'D')
    {
        return 500;
    }
    else if (c == 'M')
    {
        return 1000;
    }
    else
    {
        return 0;
    }
}
void romanOperations()
{
    Roman r2("MMMCMXCI");
    Roman r3("II");
    bool flag = true;
    do
    {
        cout << "\nRoman Number Operations:" << endl;
        cout << "1. Display Roman Numbers" << endl;
        cout << "2. Addition (r2 + r3)" << endl;
        cout << "3. Subtraction (r2 - r3)" << endl;
        cout << "4. Multiplication (r2 * r3)" << endl;
        cout << "5. Division (r2 / r3)" << endl;
        cout << "6. Equality (r2 == r3)" << endl;
        cout << "7. Inequality (r2 != r3)" << endl;
        cout << "8. Greater Than (r2 > r3)" << endl;
        cout << "9. Less Than (r2 < r3)" << endl;
        cout << "10. Post-increment (r3++)" << endl;
        cout << "11. Post-decrement (r3--)" << endl;
        cout << "12. Pre-increment (++r3)" << endl;
        cout << "13. Pre-decrement (--r3)" << endl;
        cout << "0. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Roman Notation1: " << r2.getstring() << endl;
            cout << "Integer Value1: " << r2.getInteger() << endl;
            cout << "Roman Notation2: " << r3.getstring() << endl;
            cout << "Integer Value2: " << r3.getInteger() << endl;
            break;
        case 2:
            cout << "r2 + r3: " << r2 + r3 << endl;
            break;
        case 3:
            cout << "r2 - r3: " << r2 - r3 << endl;
            break;
        case 4:
            cout << "r2 * r3: " << r2 * r3 << endl;
            break;
        case 5:
            cout << "r2 / r3: " << r2 / r3 << endl;
            break;
        case 6:
            cout << "r2 == r3: " << (r2 == r3) << endl;
            break;
        case 7:
            cout << "r2 != r3: " << (r2 != r3) << endl;
            break;
        case 8:
            cout << "r2 > r3: " << (r2 > r3) << endl;
            break;
        case 9:
            cout << "r2 < r3: " << (r2 < r3) << endl;
            break;
        case 10:
            cout << "r3++: " << r3++ << endl;
            break;
        case 11:
            cout << "r3--: " << r3-- << endl;
            break;
        case 12:
            cout << "++r3: " << ++r3 << endl;
            break;
        case 13:
            cout << "--r3: " << --r3 << endl;
            break;
        case 0:
            flag = false;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (flag);
    cout << endl
         << "Details of this code:" << endl
         << "The RomanNumber class uses encapsulation to store the integer value privately and manage conversions to/from Roman numerals. It demonstrates operator overloading for arithmetic, relational, and increment/decrement operations, and uses constructors for object initialization, allowing Roman numeral objects to behave like native types while maintaining object-oriented design principles." << endl;
}

// roman language ends here

// tronament management starts here
class Player
{
    string username;
    string playerID;
    int age;
    string country;

public:
    static int count;
    Player(string username = "", string playerID = "", int age = 0, string country = "")
    {
        this->username = username;
        this->playerID = playerID;
        this->age = age;
        this->country = country;
        count++;
    }
    virtual void display()
    {
        cout << "PLAYER DETAILS: " << endl;
        cout << " ID: " << playerID << endl;
        cout << " NAME: " << username << endl;
        cout << " AGE: " << age << endl;
        cout << " COUNTRY: " << country << endl;
    }
    int getage()
    {
        return age;
    }
    string getplayerID()
    {
        return playerID;
    }
    void setCountry(string country)
    {
        this->country = country;
    }
    virtual ~Player()
    {
        cout << "Player destroyed\n";
    }
};
int Player::count = 0;

class FPSP : public Player
{
    string fpsGameName;
    int kills;
    int deaths;

public:
    FPSP(string n = "", string id = "", int age = 0, string country = "", string name = "", int k = 0, int d = 0) : Player(n, id, age, country)
    {
        fpsGameName = name;
        kills = k;
        deaths = d;
    }
    int calculate()
    {
        return kills / deaths;
    }
    void display() override
    {
        Player::display();
        cout << "FPSP PLAYERS:" << endl;
        cout << " fpsGameName: " << fpsGameName << endl;
        cout << " kills/deaths ratio: " << calculate() << endl;
        cout << endl;
    }

    int getRatio()
    {
        return kills / deaths;
    }
    ~FPSP()
    {
    }
};

class MOBA : public Player
{
    string mobaGameName;
    int matchesPlayed;
    int winRatePercent;

public:
    MOBA(string n = "", string id = "", int age = 0, string country = "", string name = "", int k = 0, int d = 0) : Player(n, id, age, country)
    {
        mobaGameName = name;
        matchesPlayed = k;
        winRatePercent = d;
    }
    string rankCategory()
    {
        if (winRatePercent >= 80)
        {
            return "MASTER";
        }
        else if (winRatePercent < 80 && winRatePercent >= 60)
        {
            return "DIAMOND";
        }
        else if (winRatePercent < 60 && winRatePercent >= 40)
        {
            return "GOLD";
        }

        else if (winRatePercent < 40)
        {
            return "SILVER";
        }
    }
    void display() override
    {
        Player::display();
        cout << "MOBA PLAYERS:" << endl;
        cout << " mobaGameName: " << mobaGameName << endl;
        cout << " matchesPlayed: " << matchesPlayed << endl;
        cout << " rankCategory: " << rankCategory() << endl;
        cout << endl;
    }
    int getwinRate()
    {
        return winRatePercent;
    }
    ~MOBA()
    {
    }
};

void input_data(string str, Player *players[])
{
    string username;
    cout << "enter the player username: ";
    cin >> username;
    string playerID;
    cout << "enter the player id: ";
    cin >> playerID;
    int age;
    cout << "enter the player age: ";
    cin >> age;
    string country;
    cout << "enter the player country: ";
    cin >> country;
    int count = Player::count;
    if (str == "FPS")
    {
        string fpsGameName;
        cout << "enter the FPS game name: ";
        cin >> fpsGameName;
        int kills;
        cout << "enter the number of kills: ";
        cin >> kills;
        int deaths;
        cout << "enter the number of deaths: ";
        cin >> deaths;
        players[count] = new FPSP(username, playerID, age, country, fpsGameName, kills, deaths);
    }
    else if (str == "MOBA")
    {
        string mobaGameName;
        cout << "enter the moba game name: ";
        cin >> mobaGameName;
        int matchesPlayed;
        cout << "enter the number of matches played: ";
        cin >> matchesPlayed;
        int winRatePercent;
        cout << "enter the number of win rate percent: ";
        cin >> winRatePercent;
        players[count] = new MOBA(username, playerID, age, country, mobaGameName, matchesPlayed, winRatePercent);
    }
}

void highest_ratio(Player *player[])
{
    int count = Player::count;
    int max = 0;
    FPSP *bestfpsp = nullptr;
    for (int i = 0; i < count; i++)
    {
        FPSP *fpsp = dynamic_cast<FPSP *>(player[i]);
        if (fpsp)
        {
            if (fpsp->getRatio() > max)
            {
                max = fpsp->getRatio();
                bestfpsp = fpsp;
            }
        }
    }
    if (bestfpsp == nullptr)
    {
        cout << "No FPS players found.\n";
        return;
    }
    cout << "FPSP player with highest kills/deaths ratio: " << endl;
    bestfpsp->display();
}

void highest_winrate(Player *player[])
{
    int count = Player::count;
    int max = 0;
    MOBA *bestmoba = nullptr;
    for (int i = 0; i < count; i++)
    {
        MOBA *moba = dynamic_cast<MOBA *>(player[i]);
        if (moba)
        {
            if (moba->getwinRate() > max)
            {
                max = moba->getwinRate();
                bestmoba = moba;
            }
        }
    }
    if (bestmoba == nullptr)
    {
        cout << "No moba players found.\n";
        return;
    }
    cout << "Moba player with highest win rate: " << endl;
    bestmoba->display();
}

void list_players(int age, Player *p[])
{
    int count = Player::count;
    cout << "list of players above age " << age << ": " << endl;
    for (int i = 0; i < count; i++)
    {
        if (p[i]->getage() > age)
        {
            p[i]->display();
            cout << endl;
        }
    }
}

void tornament_management()
{
    Player *players[100];
    char input = 'y';

    while (input == 'y')
    {
        int choice;
        cout << "select player(1,2):" << endl;
        cout << " 1. FPS Team" << endl
             << " 2. MOBA Team" << endl;
        cin >> choice;

        if (choice == 1)
        {
            input_data("FPS", players);
        }
        else if (choice == 2)
        {
            input_data("MOBA", players);
        }
        else
        {
            cout << "Error: wrong input" << endl;
        }

        cout << "Do you want to enter the next player(y/n): ";
        cin >> input;
    }

    bool flag = true;
    while (flag)
    {
        cout << "\nPlayer Management Options:" << endl;
        cout << "1. Show total players count" << endl;
        cout << "2. Find highest ratio player" << endl;
        cout << "3. Find highest winrate player" << endl;
        cout << "4. List players with winrate > 40%" << endl;
        cout << "5. Change player country" << endl;
        cout << "6. Exit" << endl;

        int option;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option)
        {
        case 1:
            cout << "Total players count: " << Player::count << endl;
            break;
        case 2:
            highest_ratio(players);
            break;
        case 3:
            highest_winrate(players);
            break;
        case 4:
            list_players(40, players);
            break;
        case 5:
        {
            string plyid;
            cout << "Enter the player ID to change country: ";
            cin >> plyid;
            bool found = false;
            for (int i = 0; i < Player::count; i++)
            {
                if (players[i]->getplayerID() == plyid)
                {
                    string country;
                    cout << "Enter the new country name: ";
                    cin >> country;
                    players[i]->setCountry(country);
                    cout << "\nAfter changing country:" << endl;
                    players[i]->display();
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Player ID not found!" << endl;
            break;
        }
        case 6:
            flag = false;
            break;
        default:
            cout << "Invalid option!" << endl;
        }
    }

    // Cleanup
    for (int i = 0; i < Player::count; i++)
    {
        delete players[i];
    }
    cout << endl
         << "Details of this code:" << endl
         << "The system uses inheritance to create a class hierarchy where Player is the base class containing general player information, and FPSPlayer and MOBAPlayer are derived classes adding game-specific details. Each derived class overrides the display function to include specialized attributes like K/D ratio or rank category. The system supports managing multiple players, finding top performers, filtering players by age, and updating player details, all while keeping data encapsulated within classes and avoiding global variables."<<endl;

}

// tronament management ends here

// online content plaform starts here
class content{
    protected:
    int contentID;
    string title;
    int views;
    public:
    content(int id=0,string t="",int v=0):contentID(id),title(t),views(v){}
    virtual void calculatePayment()=0; 
    virtual ~content() {}
};

class vedio: public content{
 int durationMinutes;
 public:
 vedio(int id=0,string t="",int v=0,int d=0):content(id,t,v){
     durationMinutes=d;
 }
 void calculatePayment()override{
    cout<<"vedio payment: "<<endl;
    int payment=views*durationMinutes*2;
    cout<<payment<<endl;
 }

};

class article: public content{
 int wordCount;
 public:
 article(int id=0,string t="",int v=0,int w=0):content(id,t,v){
     wordCount=w;
 }
 void calculatePayment()override{
    cout<<"article payment: "<<endl;
    int payment=views*wordCount*0.05;
    cout<<payment<<endl;
 }

};

template<typename T>
class Feedback{
int contentID;
T feedbackValue;
    public:
    Feedback(int c=0,T f=T()):contentID(c),feedbackValue(f){}
    void display(){
        cout<<"contentID: "<<contentID<<endl;
        cout<<"feedbackValue: "<<feedbackValue<<endl;
    }

};



void input_data(string type,content* contentptr[],int& count){
    int contentID;
    cout<<"enter the contentID: ";
    cin>>contentID;
    string title;
    cout<<"enter the content tile: ";
    cin.ignore();
    getline(cin,title);
    int views;
    cout<<"enter the content number of views: ";
    cin>>views;
    if(type=="vedio"){
        int duration;
        cout<<"enter the time duration in minutes: ";
        cin>>duration;
        contentptr[count++]=new vedio(contentID,title,views,duration);
    }
    else if(type=="article"){
        int wordcount;
        cout<<"enter the word count of the article: ";
        cin>>wordcount;
        contentptr[count++]=new article(contentID,title,views,wordcount);
    }
}

void contentManagement()
{
    content* contentptr[100];
    int count = 0;
    bool mainFlag = true;
    
    // Create sample data
    contentptr[count++] = new vedio(1001, "clips", 1999, 10);
    contentptr[count++] = new article(1007, "current affairs", 197, 1020);
    
    Feedback<string> articlefb(201, "this article is really awesome");
    Feedback<int> vediofb(301, 1222);

    while(mainFlag) {
        cout << "\nContent Management System" << endl;
        cout << "1. Add New Content" << endl;
        cout << "2. Calculate Payments" << endl;
        cout << "3. Display Sample Feedbacks" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        
        int mainChoice;
        cin >> mainChoice;
        
        switch(mainChoice) {
            case 1: {
                bool addFlag = true;
                while(addFlag) {
                    cout << "\nSelect Content Type:" << endl;
                    cout << "1. Video" << endl;
                    cout << "2. Article" << endl;
                    cout << "3. Back to Main Menu" << endl;
                    cout << "Enter choice: ";
                    
                    int typeChoice;
                    cin >> typeChoice;
                    
                    if(typeChoice == 1) {
                        input_data("vedio", contentptr, count);
                    }
                    else if(typeChoice == 2) {
                        input_data("article", contentptr, count);
                    }
                    else if(typeChoice == 3) {
                        addFlag = false;
                        break;
                    }
                    else {
                        cout << "Invalid choice!" << endl;
                        continue;
                    }
                    
                    cout << "Do you want to add another content? (y/n): ";
                    char another;
                    cin >> another;
                    if(another != 'y' && another != 'Y') {
                        addFlag = false;
                    }
                }
                break;
            }
            
            case 2:
                if(count == 0) {
                    cout << "No content available to calculate payments!" << endl;
                } else {
                    cout << "\nCalculating Payments:" << endl;
                    for(int i = 0; i < count; i++) {
                        contentptr[i]->calculatePayment();
                    }
                }
                break;
                
            case 3:
                cout << "\nSample Feedbacks:" << endl;
                articlefb.display();
                vediofb.display();
                break;
                
            case 4:
                mainFlag = false;
                break;
                
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    // Cleanup
    for(int i = 0; i < count; i++) {
        delete contentptr[i];
    }

    cout << "\nDetails of this code:" << endl;
    cout << "The system uses polymorphism via an abstract base class Content with a pure virtual function calculatePayment(), allowing derived classes Video and Article to provide their own payment calculations at runtime. It also uses a template class Feedback<T> to handle feedback of different types (string for articles, int for videos) in a generic way. This design enables flexible management of content items, runtime payment evaluation, and type-safe feedback storage without duplicating code." << endl;
}
// online content plaform ends here


int main()
{
    bool flag = false;
    do
    {
        cout << endl
             << "OPTIONS:-" << endl;
        cout << "1. Email ID's extractor from the mails " << endl
             << "2. Polynomial calculations  " << endl
             << "3. 3D vectors and there manipulations" << endl
             << "4. My string class" << endl
             << "5. Roman counting and there manipulations" << endl
             << "6. Gaming tournament management system" << endl
             << "7. Online content platform evaluation system" << endl;
        int choice;
        flag = false;
        cout << "Enter the option number(1,2,3 etc(0 for exit)): ";
        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(999999999, '\n');
        }
        cout << endl;
        switch (choice)
        {
        case 0:
        {
            break;
        }
        case 1:
        {
            extract_email_ID_from_mails_class e1;
            e1.extract_email_ID_from_mails();
            break;
        }
        case 2:
        {
            polynomial_calculation_class p1;
            p1.polynomial_calculation();
            break;
        }
        case 3:
        {
            vectors_3D();
            break;
        }
        case 4:
        {
            my_string();
            break;
        }
        case 5:
        {
            romanOperations();
            break;
        }
        case 6:
        {
            tornament_management();
            break;
        }
        case 7:
        {
            contentManagement();
            break;
        }
        default:
        {
            cout << "Invalid choice!" << endl;
            flag = true;
        }
        }
        cout << "\nDo you want to test another code(1/0): ";
        cin >> flag;
    } while (flag);
    cout << "\nSee you again" << endl;
    return 0;
}
