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
 * @brief Defines ConsentCallback interface
 * 
 * @file consent_callback.h
 */

#ifndef API_MIP_RMS_CONSENT_CALLBACK_H_
#define API_MIP_RMS_CONSENT_CALLBACK_H_

#include <memory>

#include "mip/rms/consent.h"

namespace mip {
/**
 * @brief Collection of Consents
 */
using ConsentList = std::vector<std::shared_ptr<Consent>>;

/**
 * @brief Interface for consent request notifications
 * 
 * @note This callback is implemented by a client application to know when a consent notification should be displayed to
 * the user.
 */
class ConsentCallback {
public:
  /**
   * @brief Called when SDK requires user consent for an operation
   * 
   * @param consents The list of consents requested by SDK
   * 
   * @return Consent results
   * 
   * @note When consents are requested by the SDK, the client application should obtain consent from the user, the results
   * of each consent should be stored via Consent::Result(const ConsentResult&), and a list of the resolved consents
   * should be returned.
   */
  virtual ConsentList Consents(ConsentList& consents) = 0;
};
} // namespace mip

#endif // API_MIP_RMS_CONSENT_CALLBACK_H_
