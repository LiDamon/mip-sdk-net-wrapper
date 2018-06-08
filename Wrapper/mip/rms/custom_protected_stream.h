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
 * @brief Defines CustomProtectedStream interface
 * 
 * @file custom_protected_stream.h
 */

#ifndef API_MIP_RMS_CUSTOM_PROTECTED_STREAM_H_
#define API_MIP_RMS_CUSTOM_PROTECTED_STREAM_H_

#include "mip/mip_export.h"
#include "mip/rms/stream.h"
#include "mip/rms/user_policy.h"

namespace mip {
/**
 * @brief Wraps a stream to provide transparent encryption and decryption on read and write
 */
class CustomProtectedStream : public mip::IStream {
public:
  /**
   * @brief Wrap an existing stream as a protected stream
   * 
   * @param policy UserPolicy associated with protected content
   * @param stream Backing stream from which to read/write
   * @param contentStartPosition Starting position (in bytes) within the backing stream where protected content begins
   * @param contentSize Size (in bytes) of protected content within backing stream
   * 
   * @return Protected stream
   */
  MIP_EXPORT static std::shared_ptr<CustomProtectedStream> Create(
      std::shared_ptr<mip::UserPolicy> policy,
      mip::SharedStream stream,
      uint64_t contentStartPosition,
      uint64_t contentSize);

  /**
   * @brief Calculates size (in bytes) of content if it were to be encrypted with given policy
   * 
   * @param policy UserPolicy used to encrypt content
   * @param contentLength Size (in bytes) of unprotected content
   * 
   * @return Size (in bytes) of encrypted content
   */
  MIP_EXPORT static uint64_t GetEncryptedContentLength(
      std::shared_ptr<mip::UserPolicy> policy,
      uint64_t contentLength);

  /** @cond DOXYGEN_HIDE */
protected:
  CustomProtectedStream() {};
  /** @endcond */

};
} // namespace mip

#endif // API_MIP_RMS_CUSTOM_PROTECTED_STREAM_H_
