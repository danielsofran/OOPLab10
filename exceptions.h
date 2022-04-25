//
// Created by Daniel on 25.03.2022.
//

#ifndef LAB6_EXCEPTIONS_H
#define LAB6_EXCEPTIONS_H

#include <exception>
#include <string>
#include <utility>
#include <vector>
using std::exception;
using std::string;
using std::ostream;
using std::vector;

class MyException : public std::exception
{
protected:
    string msg;
public:
    MyException() { msg = "MyException!\n"; } ;
    explicit MyException (string  msg) : msg(std::move(msg)) {}
    const char * what() const noexcept override { return msg.c_str(); }
    friend ostream& operator<<(ostream& out, const MyException& ex) {out<<ex.msg; return out;}
};

class RepoException : public MyException { using MyException::MyException;};
class ServiceException : public MyException { using MyException::MyException;};
class InvalidFieldException : public MyException { using MyException::MyException;};

class ValidatorException : public MyException {
private:
    string sep="\n";
    vector<InvalidFieldException> errors;
public:
    //using MyException::MyException;
    explicit ValidatorException()=default;
    explicit ValidatorException (const vector<InvalidFieldException> &errors_) noexcept{
        errors = errors_;
        msg = "";
        for(const InvalidFieldException& ie : errors_)
            msg += ie.what() + sep;
    }
    ValidatorException(const ValidatorException& ve)=default;
    ValidatorException& operator=(const ValidatorException& ve) = default;
    friend ValidatorException operator+(const ValidatorException& ve1, const ValidatorException& ve2)
    {
        ValidatorException ve;
        ve.sep = ve1.sep;
        ve.errors.insert(ve.errors.end(), ve1.errors.cbegin(), ve1.errors.cend());
        ve.errors.insert(ve.errors.end(), ve2.errors.cbegin(), ve2.errors.cend());
        ve.msg = "";
        for(const InvalidFieldException& ie : ve.errors)
            ve.msg += ie.what() + ve.sep;
        return ve;
    }
    friend ValidatorException operator+(const ValidatorException& ve, const InvalidFieldException& ie)
    {
        vector<InvalidFieldException> vct{ie};
        ValidatorException ve2(vct);
        return ve + ve2;
    }
    friend ValidatorException operator+(const ValidatorException& ve, const string& msg)
    {
        return ve + InvalidFieldException(msg);
    }
    friend ValidatorException& operator+=(ValidatorException& ve1, const ValidatorException& ve2){
        ve1 = ve1 + ve2;
        return ve1;
    }
    friend ValidatorException& operator+=(ValidatorException& ve, const InvalidFieldException& ie)
    {
        ve = ve + ie;
        return ve;
    }
    friend ValidatorException& operator+=(ValidatorException& ve, const string& msg)
    {
        ve = ve + InvalidFieldException(msg);
        return ve;
    }
    explicit operator int() const {return (int)errors.size(); }
};

#endif //LAB6_EXCEPTIONS_H
