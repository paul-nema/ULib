// ============================================================================
//
// = LIBRARY
//    ULib - c++ library
//
// = FILENAME
//    usp_macro.h
//
// = AUTHOR
//    Stefano Casazza
//
// ============================================================================

#ifndef U_USP_MACRO_H
#define U_USP_MACRO_H 1

#include <ulib/all.h>

#define USP_PUTS_BUFFER              (void)UClientImage_Base::wbuffer->append(usp_buffer,usp_sz)
#define USP_PUTS_CHAR(c)             (void)UClientImage_Base::wbuffer->append(1,(c))
#define USP_PUTS_STRING(string)      (void)UClientImage_Base::wbuffer->append((string))
#define USP_PUTS_CONSTANT(string)    (void)UClientImage_Base::wbuffer->append(U_CONSTANT_TO_PARAM(string))

#define USP_PRINTF(fmt,args...)      (UClientImage_Base::_buffer->snprintf(fmt , ##args),USP_PUTS_STRING(*UClientImage_Base::_buffer))
#define USP_PRINTF_ADD(fmt,args...)   UClientImage_Base::wbuffer->snprintf_add(fmt , ##args)

#define USP_JSON_PUTS(json)                     UValue::stringify(*UClientImage_Base::wbuffer, (json))
#define USP_JSON_stringify(json,class_name,obj) ((json).toJSON(UJsonTypeHandler<class_name>(obj)), USP_JSON_PUTS(json))

#define USP_XML_PUTS(string) \
   ((void)UClientImage_Base::_encoded->reserve((string).size() * 4), \
    UXMLEscape::encode((string),*UClientImage_Base::_encoded), \
    USP_PUTS_STRING(*UClientImage_Base::_encoded))

#define USP_XML_PRINTF(fmt,args...) \
   (UClientImage_Base::_buffer->snprintf(fmt , ##args), \
    USP_XML_PUTS(*UClientImage_Base::_buffer))

#define USP_FORM_NAME(n)               (UHTTP::getFormValue(*UClientImage_Base::_value,(0+(n*2))),                *UClientImage_Base::_value)
#define USP_FORM_VALUE(n)              (UHTTP::getFormValue(*UClientImage_Base::_value,(1+(n*2))),                *UClientImage_Base::_value)
#define USP_FORM_VALUE_FROM_NAME(name) (UHTTP::getFormValue(*UClientImage_Base::_value,U_CONSTANT_TO_PARAM(name)),*UClientImage_Base::_value)

#define USP_STORAGE_VAR_GET(index,varname) \
   { \
   UString varname##_value; \
   if (UHTTP::getDataStorage(index, varname##_value)) \
      UString2Object(U_STRING_TO_PARAM(varname##_value), varname); \
   }

#define USP_STORAGE_VAR_PUT(index,varname) \
   { \
   usp_sz = UObject2String(varname, usp_buffer, sizeof(usp_buffer)); \
   UHTTP::putDataStorage(index, usp_buffer, usp_sz); \
   }

#define USP_SESSION_VAR_GET(index,varname) \
   { \
   UString varname##_value; \
   if (UHTTP::getDataSession(index, varname##_value) == false) UHTTP::setSessionCookie(); \
   else UString2Object(U_STRING_TO_PARAM(varname##_value), varname); \
   }

#define USP_SESSION_VAR_PUT(index,varname) \
   { \
   if (UHTTP::isDataSession()) \
      { \
      usp_sz = UObject2String(varname, usp_buffer, sizeof(usp_buffer)); \
      UHTTP::putDataSession(index, usp_buffer, usp_sz); \
      } \
   }

#endif
