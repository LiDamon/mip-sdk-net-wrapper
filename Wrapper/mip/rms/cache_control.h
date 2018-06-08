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
 * @brief Defines ResponseCacheFlags enum
 * 
 * @file cache_control.h
 */

#ifndef API_MIP_RMS_CACHE_CONTROL_H_
#define API_MIP_RMS_CACHE_CONTROL_H_

namespace mip {
/**
 * @brief Bit flags that dictate the caching behavior of server responses for UserPolicy aquisition
 * 
 * @note When a UserPolicy is acquired from a server, the SDK can optionally cache the policy so that future acquisition
 * attempts do not require a server request until the policy expires.
 */
enum ResponseCacheFlags {
  RESPONSE_CACHE_NOCACHE = 0x00, /**< No caching */
  RESPONSE_CACHE_INMEMORY = 0x01, /**< Results are cached in memory */
  RESPONSE_CACHE_ONDISK = 0x02, /**< Results are cached on disk */
  RESPONSE_CACHE_CRYPTED = 0x04, /**< Disk-cached results are encrypted */
};
} // namespace mip

#endif // API_MIP_RMS_CACHE_CONTROL_H_

