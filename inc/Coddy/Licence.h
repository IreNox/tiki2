////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_LICENCE_H
#define CLODDY_KERNEL_LICENCE_H

#include "CodeX/System_Native.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class IFile; } } } }
namespace Cloddy { namespace Core { namespace Logging { class ILogger; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace Cloddy { namespace Core { namespace Logging { class LoggingHelper; } } }
namespace Cloddy { namespace Kernel { class CloddyKernel; } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Kernel::Licence.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Files::IFile;
  using Cloddy::Core::Logging::ILogger;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using Cloddy::Core::Logging::LoggingHelper;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  This class represents the licence under which the CloddySDk runs.
   */
  class Licence : public virtual Object
  {
    // Declare friend classes.
    
    friend class CloddyKernel;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Clears the currently used licence (allows for setting another one).
     */
    static void Clear();
    
    /*!
     * @brief  Sets the licence to use for the CloddySDK.
     * 
     * @param pathToLicenceFile <b>[not-empty]</b>  Path to the licence file.
     */
    static void Set(String pathToLicenceFile);
    
    /*!
     * @brief  Sets the licence to use for the CloddySDK.
     * 
     * @param pathToLicenceFile <b>[not-null]</b>  Path to the licence file.
     */
    static void Set(Path* pathToLicenceFile);
    
    /*!
     * @brief  Sets the licence to use for the CloddySDK.
     * 
     * @param licenceFile <b>[not-null]</b>  The licence file.
     */
    static void Set(IFile* licenceFile);
    
    /*!
     * @brief  Sets the licence to use for the CloddySDK.
     * 
     * @param licenceFile <b>[not-null]</b>  The contents of the licence file.
     */
    static void Set(ByteBuffer* licenceFile);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Size of an encrypted licence descriptor,in bytes.
     */
    static const int32 EncryptedLicenceDescriptorSize = 1024;
    
    /*!
     * @brief  Used to cast \c int  values to unsigned 32-bit integers.
     */
    static const int64 IntMask = (int64) 0xFFFFFFFFULL;
    
    /*!
     * @brief  Size of a plain licence descriptor,in bytes.
     */
    static const int32 PlainLicenceDescriptorSize = 1016;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Version of the application.
     * 
     * @return The licence field value.
     */
    static String GetApplicationName();
    
    /*!
     * @brief  Licence grant date.
     * 
     * @return The licence field value.
     */
    static String GetApplicationPlatform();
    
    /*!
     * @brief  The licence type.
     * 
     * @return The licence field value.
     */
    static String GetApplicationVersion();
    
    /*!
     * @brief  Name of the company department.
     * 
     * @return The licence field value.
     */
    static String GetCompanyAddress1();
    
    /*!
     * @brief  Location of the company department.
     * 
     * @return The licence field value.
     */
    static String GetCompanyAddress2();
    
    /*!
     * @brief  Name of the company.
     * 
     * @return The licence field value.
     */
    static String GetCompanyName();
    
    /*!
     * @brief  Name of the application.
     * 
     * @return The licence field value.
     */
    static String GetContact();
    
    /*!
     * @brief  The precomputed CRC table.
     */
    static const Array<int32> CrcTable;
    
    /*!
     * @brief  Platform of the application.
     * 
     * @return The licence field value.
     */
    static String GetExpirationDate();
    
    /*!
     * @brief  Name of the user.
     * 
     * @return The licence field value.
     */
    static String GetLicenceDate();
    
    /*!
     * @brief  The licenced SDK.
     * 
     * @return The licence field value.
     */
    static String GetLicenceSDK();
    
    /*!
     * @brief  Licence expiration date.
     * 
     * @return The licence field value.
     */
    static String GetLicenceType();
    
    /*!
     * @brief  The logger object of this class.
     */
    static const StaticPtr<ILogger> Logger;
    
    /*!
     * @brief  The exponent big integer of the public key.
     */
    static const Array<int32> PublicExponent;
    
    /*!
     * @brief  The modulus big integer of the public key.
     */
    static const Array<int32> PublicModulus;
    
    /*!
     * @brief  The licence descriptor.
     */
    static Ptr<Licence> currentLicence;
    
    /*!
     * @brief  Version of the application.
     */
    String applicationName;
    
    /*!
     * @brief  Licence grant date.
     */
    String applicationPlatform;
    
    /*!
     * @brief  The licence type.
     */
    String applicationVersion;
    
    /*!
     * @brief  Name of the company department.
     */
    String companyAddress1;
    
    /*!
     * @brief  Location of the company department.
     */
    String companyAddress2;
    
    /*!
     * @brief  Name of the company.
     */
    String companyName;
    
    /*!
     * @brief  Name of the application.
     */
    String contact;
    
    /*!
     * @brief  Platform of the application.
     */
    String expirationDate;
    
    /*!
     * @brief  Name of the user.
     */
    String licenceDate;
    
    /*!
     * @brief  The licenced SDK.
     */
    String licenceSDK;
    
    /*!
     * @brief  Licence expiration date.
     */
    String licenceType;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Licence.
     * 
     * @param licenceDescriptor The licence descriptor.
     */
    Licence(ByteBuffer* licenceDescriptor);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Compares the given big integers.
     * 
     * @param x The first big integer.
     * @param y The second big integer.
     * 
     * @return \c -1  if \e x  &lt; \e y ,\c 0  if \e x  =\e y  and \c 1  if \e x  >\e y .
     */
    static int32 Compare(Array<int32> x, Array<int32> y);
    
    /*!
     * @brief  Compares the given big integers.
     * 
     * Leading zero values of both big integers are ignored for the comparison.
     * 
     * @param x The first big integer.
     * @param xOffset Offset into \e x  to first significant value.
     * @param y The second big integer.
     * @param yOffset Offset into \e y  to first significant value.
     * 
     * @return \c -1  if \e x  &lt; \e y ,\c 0  if \e x  =\e y  and \c 1  if \e x  >\e y .
     */
    static int32 CompareNoLeadingZeroes(Array<int32> x, int32 xOffset, Array<int32> y, int32 yOffset);
    
    /*!
     * @brief  Computes the m quote value for the given big integer that is necessary for 
     *         the #ModPow operation.
     * 
     * @param bitInteger The big integer.
     * 
     * @return The m quote value.
     */
    static int64 ComputeMQuote(Array<int32> bitInteger);
    
    /*!
     * @brief  Decrypts the given licence descriptor.
     * 
     * @param inputBuffer The encrypted licence descriptor.
     * @param outputBuffer The plain licence descriptor.
     */
    static void Decrypt(ByteBuffer* inputBuffer, ByteBuffer* outputBuffer);
    
    /*!
     * @brief  Creates a big integer from the given ByteBuffer.
     * 
     * @param buffer The ByteBuffer that holds the digits of the big integer.
     * 
     * @return The big integer.
     */
    static Array<int32> FromBuffer(ByteBuffer* buffer);
    
    /*!
     * @brief  Computes the bit length of the given bit integer.
     * 
     * @param bigInteger The big integer.
     * @param firstSignificant Offset into \e bigInteger  to first significant value.
     * 
     * @return The bit length.
     */
    static int32 GetBitLength(Array<int32> bigInteger, int32 firstSignificant);
    
    /*!
     * @brief  Computes the bit length of the given value.
     * 
     * @param v The value.
     * 
     * @return The bit length.
     */
    static int32 GetBitLength(int32 v);
    
    /*!
     * @brief  Computes the combined modulus/exponent of the given big integer,.
     * 
     * @param value The input big integer.
     * @param exponent The exponent big integer.
     * @param modulus The modulus big integer.
     * @param mQuote The precomputed m quote value (#ComputeMQuote).
     * 
     * @return The resulting big integer.
     */
    static Array<int32> ModPow(Array<int32> value, Array<int32> exponent, Array<int32> modulus, int64 mQuote);
    
    /*!
     * @brief  Performs a multiplication on the given big integers.
     * 
     * @param a Big integer.
     * @param x Big integer.
     * @param y Big integer.
     * @param m Big integer.
     * @param mQuote The precomputed m quote value (#ComputeMQuote.
     */
    static void Multiply(Array<int32> a, Array<int32> x, Array<int32> y, Array<int32> m, int64 mQuote);
    
    /*!
     * @brief  Computes the remainder of the quotient of the given \e dividend  and \e divisor .
     * 
     * Computation is performed in place;the resulting remainder will be stored in \e dividend .
     * 
     * @param dividend The dividend.
     * @param divisor The divisor.
     */
    static void Remainder(Array<int32> dividend, Array<int32> divisor);
    
    /*!
     * @brief  Performs a bitwise left shift on the given big integer.
     * 
     * @param bigInteger The big integer.
     * @param bitsToShift The number of bits to shift.
     * 
     * @return The resulting big integer.
     */
    static Array<int32> ShiftLeft(Array<int32> bigInteger, int32 bitsToShift);
    
    /*!
     * @brief  Performs a bitwise right shift on the given big integer.
     * 
     * The computation is performed in place;the resulting big integer will be stored 
     * in \e bigInteger .
     * 
     * @param bigInteger The big integer.
     * @param firstSignificant Offset into \e bigInteger  to first significant value.
     * @param bitsToShift The number of bits to shift.
     */
    static void ShiftRight(Array<int32> bigInteger, int32 firstSignificant, int32 bitsToShift);
    
    /*!
     * @brief  Performs a bitwise right shift of one bit on the given big integer.
     * 
     * The computation is performed in place;the resulting big integer will be stored 
     * in \e bigInteger .
     * 
     * @param bigInteger The big integer.
     * @param firstSignificant Offset into \e bigInteger  to first significant value.
     */
    static void ShiftRightOne(Array<int32> bigInteger, int32 firstSignificant);
    
    /*!
     * @brief  Subtracts the given big integers:<c>left - right</c>.
     * 
     * The computation is performed in place;the resulting big integer will be stored in \e left .
     * 
     * @param left The left big integer.
     * @param leftOffset Offset into \e left  to first significant value.
     * @param right The right big integer.
     */
    static void Subtract(Array<int32> left, int32 leftOffset, Array<int32> right);
    
    /*!
     * @brief  Writes the digits of the given big integer to the specified ByteBuffer.
     * 
     * @param bigInteger The big integer.
     * @param buffer The output ByteBuffer.
     */
    static void ToBuffer(Array<int32> bigInteger, ByteBuffer* buffer);
    
    /*!
     * @brief  Trims all leading zero values from the given big integer.
     * 
     * @param bigInteger The big integer.
     * 
     * @return The resulting big integer.
     */
    static Array<int32> TrimLeadingZeros(Array<int32> bigInteger);
    
    /*!
     * @brief  Validates that a licence has been set.
     * 
     * @exception CoreException If the licence has not been set yet.
     */
    static void Validate();
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field Logger.
     */
    static Object* StaticInitializer_Logger();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Licence> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD91F89AA;
    
    /*!
     * @brief Tries to cast this object to the given type.
     *
     * @param typeId The ID of the type to cast to.
     *
     * @return The result of the type cast. Can be \c 0 if the requested cast is an invalid 
     *         downcast.
     */
    protected: virtual void* TryCast(int typeId)
    {
      if (typeId == TypeId) return (void*) this;
      return (void*) 0;
    }
    
    // ---------------------------------------------------------------------------------------------
    // Native code
    // ---------------------------------------------------------------------------------------------
    
    NATIVE_BLOCK_BEGIN ("69B32765-BAE1-456B-B64E-24E2E1459EAD")
    
    // Nothing to do here.
    
    NATIVE_BLOCK_END   ("69B32765-BAE1-456B-B64E-24E2E1459EAD")
  };
  
} } 

#endif
