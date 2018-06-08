/**
 *
 * Copyright (c) Microsoft Corporation.
 * All rights reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
/**
 * @brief Defines RMS-specific exceptions
 * 
 * @file rms_exceptions.h
 */

#ifndef API_MIP_RMS_RMS_EXCEPTIONS_H_
#define API_MIP_RMS_RMS_EXCEPTIONS_H_

#include <algorithm>
#include <cstring>
#include <exception>
#include <string>

#ifndef _NOEXCEPT
# if __GNUC__ >= 4
#  define _NOEXCEPT _GLIBCXX_USE_NOEXCEPT
# endif // if __GNUC__ >= 4
#endif  // ifndef _NOEXCEPT

namespace mip {

/**
 * @brief Maximum length of exception message string
 * 
 * Exception messages longer than this value will be truncated
 */
#define MAX_EXCEPTION_MESSAGE_LENGTH 255

/**
 * @brief Base RMS exception
 */
class RMSException : public std::exception {
public:

  /**
   * @brief Classification of exception
   */
  enum class ExceptionTypes : int {
    LogicError = 0 /**< General logic error */
  };

  /**
   * @brief Classification of error type
   */
  enum class ErrorTypes : int {
    InvalidArgument = 0, /**< Invalid argument */
    NullPointer, /**< Null pointer */
    NotFound, /**< Not found */
    NetworkError, /**< Network error */
    CryptoError, /**< Crypto error */
    StreamError, /**< Stream error */
    PFileError, /**< PFile error */
    RightsError, /**< Rights error */
    OfficeFileError, /**< Office file error */
    NotSupported, /**< Not supported */
    FileError, /**< General file error */
    JsonParseError, /**< JSON parse error */
  };

  /**
   * @brief RMSException constructor
   * 
   * @param type Type of exception
   * @param error Error code
   * @param message Exception message
   */
  RMSException(const ExceptionTypes type, const int error, const std::string& message) _NOEXCEPT
      : mType(type), mError(error) {
    CopyMessage(message.c_str(), message.length());
  }

  /**
   * @brief RMSException constructor
   * 
   * @param type Type of exception
   * @param error Error code
   * @param message Exception message
   */
  RMSException(const ExceptionTypes type, const int error, const char* const& message) _NOEXCEPT
      : mType(type), mError(error) {
    CopyMessage(message, strlen(message));
  }

  /** @cond DOXYGEN_HIDE */
  virtual ~RMSException() _NOEXCEPT {}
  /** @endcond */

  /**
   * @brief Gets exception message
   * 
   * @return Exception message
   */
  virtual const char* what() const _NOEXCEPT override { return mMessage; }

  /**
   * @brief Gets exception type
   * 
   * @return Exception type
   */
  virtual ExceptionTypes type() const _NOEXCEPT { return mType; }

  /**
   * @brief Gets error code
   * 
   * @return Error code
   */
  virtual int error() const _NOEXCEPT { return mError; }

private:
  void CopyMessage(const char* msg, const size_t len) {
    size_t mlen = (std::min)(len, static_cast<const size_t>(MAX_EXCEPTION_MESSAGE_LENGTH - 1));

    memset(mMessage, 0, sizeof(mMessage));

    if (mlen > 0) {
#ifdef Q_OS_WIN32
      memcpy_s(mMessage, mlen, msg, mlen);
#else // ifdef Q_OS_WIN32
      memcpy(mMessage, msg, mlen);
#endif // ifdef Q_OS_WIN32
    }
  }

  ExceptionTypes mType;
  int mError;
  char mMessage[MAX_EXCEPTION_MESSAGE_LENGTH];
};

/**
 * @brief RMS logic exception
 */
class RMSLogicException : public RMSException {
public:
  /**
   * @brief RMSLogicException constructor
   * 
   * @param error Error code
   * @param message Exception message
   */
  RMSLogicException(const ErrorTypes error, const std::string& message) _NOEXCEPT
      : RMSException(ExceptionTypes::LogicError, static_cast<int>(error), message) {}

  /**
   * @brief RMSLogicException constructor
   * 
   * @param error Error code
   * @param message Exception message
   */
  RMSLogicException(const ErrorTypes error, const char* const& message) _NOEXCEPT
      : RMSException(ExceptionTypes::LogicError, static_cast<int>(error), message) {}
};

/**
 * @brief RMS invalid argument exception
 */
class RMSInvalidArgumentException : public RMSLogicException {
public:
  /**
   * @brief RMSInvalidArgumentException constructor
   * 
   * @param message Exception message
   */
  RMSInvalidArgumentException(const std::string& message) _NOEXCEPT
      : RMSLogicException(ErrorTypes::InvalidArgument, message) {}

  /**
   * @brief RMSInvalidArgumentException constructor
   * 
   * @param message Exception message
   */
  RMSInvalidArgumentException(const char* const& message) _NOEXCEPT
      : RMSLogicException(ErrorTypes::InvalidArgument, message) {}
};

/**
 * @brief RMS null pointer exception
 */
class RMSNullPointerException : public RMSLogicException {
public:
  /**
   * @brief RMSNullPointerException constructor
   * 
   * @param message Exception message
   */
  RMSNullPointerException(const std::string& message) _NOEXCEPT
      : RMSLogicException(ErrorTypes::NullPointer, message) {}

  /**
   * @brief RMSNullPointerException constructor
   * 
   * @param message Exception message
   */
  RMSNullPointerException(const char* const& message) _NOEXCEPT
      : RMSLogicException(ErrorTypes::NullPointer, message) {}
};

/**
 * @brief RMS not found exception
 */
class RMSNotFoundException : public RMSLogicException {
public:
  /**
   * @brief RMSNotFoundException constructor
   * 
   * @param message Exception message
   */
  RMSNotFoundException(const std::string& message) _NOEXCEPT
      : RMSLogicException(ErrorTypes::NullPointer, message) {}

  /**
   * @brief RMSNotFoundException constructor
   * 
   * @param message Exception message
   */
  RMSNotFoundException(const char* const& message) _NOEXCEPT
      : RMSLogicException(ErrorTypes::NullPointer, message) {}
};

/**
 * @brief RMS Network exception
 */
class RMSNetworkException : public RMSLogicException {
public:

  /**
   * @brief Classification of network failure
   */
  enum class Reason : int {
    ServerError = 0, /**< Server error */
    UserNotConsented, /**< User did not consent */
    ServiceNotAvailable, /**< Service not available */
    OnPremNotSupported, /**< On-prem not supported */
    InvalidPL, /**< Invalid publishing license */
    ServiceDisabled, /**< Service disabled */
    DeviceRejected, /**< Device rejected */
    NeedsOnline, /**< Requires online access */
    CancelledByUser, /**< Cancelled by user */
  };

  /**
   * @brief RMSNetworkException constructor
   * 
   * @param message Exception message
   * @param reason Network failure classification
   */
  RMSNetworkException(const std::string& message, Reason reason) _NOEXCEPT
      : RMSLogicException(ErrorTypes::NetworkError, message), mReason(reason) {}

  /**
   * @brief RMSNetworkException constructor
   * 
   * @param message Exception message
   * @param reason Network failure classification
   */
  RMSNetworkException(const char* const& message, Reason reason) _NOEXCEPT
      : RMSLogicException(ErrorTypes::NetworkError, message), mReason(reason) {}

  /**
   * @brief Gets network failure classification
   * @return Network failure classification
   */
  virtual Reason reason() const _NOEXCEPT { return mReason; }

private:
  Reason mReason;
};

/**
 * @brief RMS cryptography exception
 */
class RMSCryptographyException : public RMSLogicException {
public:
  /**
   * @brief RMSCryptographyException constructor
   * 
   * @param message Exception message
   */
  RMSCryptographyException(const std::string& message) _NOEXCEPT
      : RMSLogicException(ErrorTypes::NetworkError, message) {}

  /**
   * @brief RMSCryptographyException constructor
   * 
   * @param message Exception message
   */
  RMSCryptographyException(const char* const& message) _NOEXCEPT
      : RMSLogicException(ErrorTypes::NetworkError, message) {}
};

/**
 * @brief RMS stream exception
 */
class RMSStreamException : public RMSLogicException {
public:
  /**
   * @brief RMSStreamException constructor
   * 
   * @param message Exception message
   */
  RMSStreamException(const std::string& message) _NOEXCEPT
      : RMSLogicException(ErrorTypes::StreamError, message) {}

  /**
   * @brief RMSStreamException constructor
   * 
   * @param message Exception message
   */
  RMSStreamException(const char* const& message) _NOEXCEPT
      : RMSLogicException(ErrorTypes::StreamError, message) {}
};

/**
 * @brief RMS PFile exception
 */
class RMSPFileException : public RMSLogicException {
public:
  /**
   * @brief Classification of PFile failure
   */
  enum class Reason : int {
    NotPFile = 0, /**< Not a PFile */
    NotSupportedVersion, /**< Unsupported version */
    BadArguments, /**< Bad arguments */
    CorruptFile, /**< Corrupt file */
    AlreadyProtected, /**< Already protected */
  };

  /**
   * @brief RMSPFileException constructor
   * 
   * @param message Exception message
   * @param reason PFile error classification
   */
  RMSPFileException(const std::string& message, Reason reason) _NOEXCEPT
      : RMSLogicException(ErrorTypes::PFileError, message), mReason(reason) {}

  /**
   * @brief RMSPFileException constructor
   * 
   * @param message Exception message
   * @param reason PFile error classification
   */
  RMSPFileException(const char* const& message, Reason reason) _NOEXCEPT
      : RMSLogicException(ErrorTypes::PFileError, message), mReason(reason) {}

  /**
   * @brief Gets PFile error classification
   * 
   * @return PFile error classification
   */
  virtual Reason reason() const _NOEXCEPT { return mReason; }

private:
  Reason mReason; // additional reason for this error
};

/**
 * @brief RMS rights exception
 */
class RMSRightsException : public RMSLogicException {
public:
  /**
   * @brief RMSRightsException constructor
   * 
   * @param message Exception message
   */
  RMSRightsException(const std::string& message) _NOEXCEPT
      : RMSLogicException(ErrorTypes::RightsError, message) {}

  /**
   * @brief RMSRightsException constructor
   * 
   * @param message Exception message
   */
  RMSRightsException(const char* const& message) _NOEXCEPT
      : RMSLogicException(ErrorTypes::RightsError, message) {}
};

/**
 * @brief RMS Office file exception
 */
class RMSOfficeFileException : public RMSLogicException {
public:
  /**
   * @brief Office file failure classification
   */
  enum class Reason : int {
    NotOfficeFile = 0, /**< Not an Office file */
    BadArguments, /**< Bad arguments */
    CorruptFile, /**< Corrupt file */
    NotProtected, /**< Not protected */
    NonRMSProtected, /**< Not RMS protected */
    AlreadyProtected, /**< Already protected */
    CompoundFileError, /**< Compound file error */
    Unknown, /**< Unknown */
  };

  /**
   * @brief RMSOfficeFileException constructor
   * 
   * @param message Exception message
   * @param reason Office file failure classification
   */
  RMSOfficeFileException(const std::string& message, Reason reason) _NOEXCEPT
    : RMSLogicException(ErrorTypes::OfficeFileError, message), mReason(reason) {}

  /**
   * @brief RMSOfficeFileException constructor
   * 
   * @param message Exception message
   * @param reason Office file failure classification
   */
  RMSOfficeFileException(const char* const& message, Reason reason) _NOEXCEPT
    : RMSLogicException(ErrorTypes::OfficeFileError, message), mReason(reason) {}

  /**
   * @brief Gets Office file failure classification
   * 
   * @return Office file failure classification
   */
  virtual Reason reason() const _NOEXCEPT { return mReason; }

private:
  Reason mReason; // additional reason for this error
};

} // namespace mip

#endif // API_MIP_RMS_RMS_EXCEPTIONS_H_
