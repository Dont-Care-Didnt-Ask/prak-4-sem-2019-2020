#include <cstring>
#include <string>

/* Several CopyOnWriteStr objects can point
 * to a single Content box.
 * It contains a pointer to actual string - array of chars,
 * the length of the string, including \0
 * and the amount of variables, sharing this string.
 */
struct ContentBox
{
    char *str = nullptr;
    std::size_t allocated = 0;
    mutable std::size_t cnt = 0;
};

// Implementation class for String.
class CopyOnWriteStr
{
private:
    ContentBox *content;
    void get_own_content();

public:
    CopyOnWriteStr();
    CopyOnWriteStr(const char * str);
    CopyOnWriteStr(const CopyOnWriteStr& other);

    ~CopyOnWriteStr();

    CopyOnWriteStr& operator = (const CopyOnWriteStr& other);
    CopyOnWriteStr& operator += (const CopyOnWriteStr& other);

    operator std::string() const;

    class Proxy;
    Proxy operator [] (std::size_t idx);
};

// I'll need a proxy class to define the operator [].
// (Check the comments around lines 164 and 171)
class CopyOnWriteStr::Proxy
{
    friend CopyOnWriteStr::Proxy CopyOnWriteStr::operator [](std::size_t idx);
private:
    CopyOnWriteStr *src = nullptr;
    std::size_t idx = 0;

    // I don't want a random user to create a Proxy object, so the constructor is private.
    Proxy(CopyOnWriteStr *p, std::size_t i);
public:
    operator char() const;

    Proxy& operator=(char sym);
    Proxy& operator=(const Proxy& other);
};

//
// Implementation of constructors, destructor and function-members of CopyOnWriteStr.
//

// We have to get a unique ContentBox instance, if we're gonna change it.
void CopyOnWriteStr::get_own_content() {
    ContentBox *my_ptr = new ContentBox;

    my_ptr->str = new char[content->allocated];
    snprintf(my_ptr->str, content->allocated, "%s", content->str);

    my_ptr->allocated = content->allocated;
    
    my_ptr->cnt = 1;
    content->cnt--;
    /* 
     content->cnt won't (shouldn't) become zero, 
     because get_own_content() is called only
     if content->cnt > 1.
    */
    content = my_ptr;
}

CopyOnWriteStr::CopyOnWriteStr() {
    content = new ContentBox;
    content->str = new char[1];
    content->str[0] = '\0';
    content->allocated = 1;
    content->cnt = 1;
}

CopyOnWriteStr::CopyOnWriteStr(const char * str) {
    content = new ContentBox;
    
    std::size_t len = strlen(str) + 1;
    content->allocated = len;

    content->str = new char[len];
    snprintf(content->str, len, "%s", str);

    content->cnt = 1;
}

CopyOnWriteStr::CopyOnWriteStr(const CopyOnWriteStr& other) {
    content = other.content;    // Not making a copy yet.
    content->cnt++;
}

CopyOnWriteStr::~CopyOnWriteStr(){
    if (content) {
        content->cnt--;
        if (content->cnt == 0) {    // Check if somebody needs the Content Box anymore.
            delete [] content->str;
            delete content;
        }
    }
}

CopyOnWriteStr& CopyOnWriteStr::operator = (const CopyOnWriteStr& other)
{
    if (this != &other) {
        content->cnt--;
        if (content->cnt == 0) {
            delete [] content->str;
            delete content;
        }

        content = other.content;
        content->cnt++;
    }
    return *this;
}

CopyOnWriteStr& CopyOnWriteStr::operator += (const CopyOnWriteStr& other)
{
    if (content->cnt > 1) {
        get_own_content();
    }
    std::size_t new_len = content->allocated + other.content->allocated - 1;
    // -1 since a byte for '\0' was counted twice.

    char *new_str = new char[new_len];
    content->allocated = new_len;

    snprintf(new_str, new_len, "%s%s", content->str, other.content->str);
    
    delete [] content->str;
    content->str = new_str;
    // should work in case 
    //   String a = "bebebe"; a += a;
    // since we first make a new string and then delete the old one.

    return *this;
}

CopyOnWriteStr::operator std::string() const {
    return std::string(content->str);
}

//
// Proxy class implementation.
//

CopyOnWriteStr::Proxy::Proxy(CopyOnWriteStr *p, std::size_t i) : src(p), idx(i)
{}

// If the user wants to take a look at symbol (not changing it) –
// just give it to him. We don't need to make a copy.
CopyOnWriteStr::Proxy::operator char() const
{
    return src->content->str[idx];
}

// Otherwise, we have to check if we share the resource
// and make a copy, if necessary.
CopyOnWriteStr::Proxy& CopyOnWriteStr::Proxy::operator=(char sym)
{
    if (src->content->cnt > 1) {
        src->get_own_content();
    }
    src->content->str[idx] = sym;
    return *this;
}

CopyOnWriteStr::Proxy& CopyOnWriteStr::Proxy::operator=(const Proxy& other)
{
    if (src->content->cnt > 1) {
        src->get_own_content();
    }
    src->content->str[idx] = char(other);
    return *this;
}

// Now we can define operator[]
auto CopyOnWriteStr::operator[](std::size_t idx) -> CopyOnWriteStr::Proxy
{
    return Proxy(this, idx); 
}

//
// Finally, String class.
//

class String
{
private:
    CopyOnWriteStr *ptr = nullptr;
public:
    String();
    String(const char * str);
    String(const String& other);
    String(String&& other);

    ~String();

    String& operator = (const String& other);
    String& operator = (String&& other);

    String& operator += (const String& other);

    operator std::string();

    CopyOnWriteStr::Proxy operator [](std::size_t idx);
    char operator [](std::size_t) const;
};

//
// String implementation.
//

String::String(): ptr(new CopyOnWriteStr())
{}
String::String(const char * str): ptr(new CopyOnWriteStr(str))
{}
String::String(const String& other): ptr(new CopyOnWriteStr(*other.ptr))
{}

String::String(String&& other): ptr(other.ptr)
{
    other.ptr = nullptr;
}

String::~String(){
    delete ptr;
    // CopyOnWriteStr destructor is called automaticaly.
}

String& String::operator = (const String& other)
{
    *ptr = *other.ptr;
    return *this;
}

String& String::operator = (String&& other) 
{
    if (this != &other) {        
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    return *this;
}

String& String::operator +=(const String& other)
{
    *ptr += *other.ptr;
    return *this;
}

String::operator std::string() {
    return std::string(*ptr);
}

CopyOnWriteStr::Proxy String::operator [](std::size_t idx)
{
    return (*ptr)[idx];
}

char String::operator [](std::size_t idx) const 
{
    return static_cast<char>( (*ptr)[idx] );
}