/* 
 * File:   optional.h
 * Author: tjoppen
 *
 * Created on December 13, 2010, 4:44 PM
 */

#ifndef _OPTIONAL_H
#define	_OPTIONAL_H

#include "Exceptions.h"

namespace james {
    /**
     * Like boost::optional, except with pointer storage.
     *
     * Note: This may be quite slow for built-in types like int. Consider using
     *       boost::optional in that case.
     */
    template<class T> class optional {
        T *t;

        void assign(const T *rhs) {
            if(!rhs) {
                if(t) {
                    delete t;
                    t = NULL;
                }

                return;
            }

            T *newT = new T(*rhs);

            if(t)
                delete t;

            t = newT;
        }

        void throwIfNotSet() const {
            if(!isSet())
                throw UnsetOptionalException("Tried to access optional value that isn't set");
        }
    public:
        optional() : t(NULL) {
        }

        optional(const T& t) : t(NULL) {
            assign(&t);
        }

        optional(const optional& other) : t(NULL) {
            assign(other.t);
        }

        ~optional() {
            if(t)
                delete t;
        }

        operator bool () const {
            return t;
        }

        bool isSet() const {
            return t;
        }

        optional& operator = (const T& rhs) {
            assign(&rhs);
            return *this;
        }

        optional& operator = (const optional& rhs) {
            assign(rhs.t);
            return *this;
        }

        const T* operator -> () const {
            throwIfNotSet();

            return t;
        }

        T* operator -> () {
            throwIfNotSet();

            return t;
        }

        const T& get() const {
            throwIfNotSet();

            return *t;
        }

        T& get() {
            throwIfNotSet();

            return *t;
        }

        const T& operator * () const {
            return get();
        }

        T& operator * () {
            return get();
        }
    };
}

#endif	/* _OPTIONAL_H */

