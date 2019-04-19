#pragma once
#include <iostream>

enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';
    std::ostream& out_;

public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }

private:
    Error process_one(uint64_t val)
    {
        out_ << val << Separator;
        return Error::NoError;
    }

    Error process_one(bool val)
    {
        if (val) {
            out_ << "true" << Separator;
        }
        else {
            out_ << "false" << Separator;
        }
        return Error::NoError;
    }

    template <class T>
    Error process(T&& val)
    {
        return process_one(std::forward<T>(val));
    }

    template <class T, class... Args>
    Error process(T&& val, Args&&... args)
    {
        if (process_one(std::forward<T>(val)) != Error::NoError) {
            return Error::CorruptedArchive;
        }
        return process(std::forward<Args>(args)...);
    }
};

class Deserializer {
    static constexpr char Separator = ' ';
    std::istream& in_;

public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args)
    {
        return process(args...);
    }

private:
    Error process_one(bool& val)
    {
        std::string txt;
        in_ >> txt;

        if (txt == "true") {
            val = true;
            return Error::NoError;
        }
        if (txt == "false") {
            val = false;
            return Error::NoError;
        }

        return Error::CorruptedArchive;
    }

    Error process_one(uint64_t& val)
    {

        int64_t num;
        in_ >> num;

        if (num < 0) {
	        return Error::CorruptedArchive;
        }

        val = num;
        return Error::NoError;
    }

    template <class T>
    Error process(T&& val)
    {
        return process_one(std::forward<T>(val));
    }

    template <class T, class... Args>
    Error process(T&& val, Args&&... args)
    {
        if (process_one(std::forward<T>(val)) != Error::NoError) {
            return Error::CorruptedArchive;
        }
        return process(std::forward<Args>(args)...);
    }
};