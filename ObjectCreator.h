#ifndef OBJECTCREATOR_H
#define OBJECTCREATOR_H

#include <boost/shared_ptr.hpp>

template <typename T>
///
/// \brief The ObjectCreator class
/// create object about T
///
class ObjectCreator
{
public:
    boost::shared_ptr<T> operator ()()
    {
        return boost::shared_ptr<T>(new T());
    }

};

#endif // OBJECTCREATOR_H
