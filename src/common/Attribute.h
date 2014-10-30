/** 
 * @file Attribute.h 
 * Attribute class declaration
 */

#ifndef CALI_ATTRIBUTE_H
#define CALI_ATTRIBUTE_H

#include "cali_types.h"

#include "IdType.h"
#include "RecordMap.h"

#include <string>

namespace cali
{
    class AttributeStore;

    class Attribute : public IdType {
        std::string    m_name;
        int            m_properties;
        cali_attr_type m_type;

        Attribute(cali_id_t            id,
                  const std::string&  name, 
                  cali_attr_type       type,
                  int                 properties);

        friend class AttributeStore;

    public:

        Attribute(const Attribute&) = default;
        Attribute(Attribute&&) = default;

        Attribute& operator = (const Attribute&) = default;

        std::string    name() const { return m_name; }
        cali_attr_type type() const { return m_type; }        

        int            properties() const { return m_properties; } 

        bool store_as_value() const { 
            return m_properties & CALI_ATTR_ASVALUE; 
        }
        bool is_autocombineable() const   { 
            return !store_as_value() && !(m_properties & CALI_ATTR_NOMERGE);
        }
        bool is_global() const {
            return m_properties & CALI_ATTR_GLOBAL;
        }

        RecordMap record() const;
        static Attribute read(const RecordMap&);

        static const Attribute invalid;
    };

} // namespace cali

#endif // CALI_ATTRIBUTE_H