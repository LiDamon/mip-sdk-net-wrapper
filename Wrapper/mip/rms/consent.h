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
 * @brief Defines Consent interface
 * 
 * @file consent.h
 */

#ifndef API_MIP_RMS_CONSENT_H_
#define API_MIP_RMS_CONSENT_H_

#include <string>
#include <vector>

#include "mip/rms/consent_type.h"
#include "mip/rms/consent_result.h"

namespace mip {
/**
 * @brief Represents a user's acceptance/refusal to allow an action
 */
class Consent {
public:
  /**
   * @brief Gets the result of a consent request.
   * 
   * @return Result of consent request
   */
  virtual const mip::ConsentResult& Result() const = 0;

  /**
   * @brief Sets the result of a consent request
   * 
   * @param value Result of consent request
   */
  virtual void Result(const ConsentResult& value) = 0;

  /**
   * @brief Gets the type of consent
   * 
   * @return Type of consent
   */
  virtual mip::ConsentType Type() const = 0;

  /**
   * @brief Gets the URLs involved in the consent request
   * 
   * @return URLs involved in the consent request
   */
  virtual const std::vector<std::string> Urls() const = 0;

  /**
   * @brief Gets the user (email address) from whom consent is requested
   * 
   * @return User from whom consent is requested
   */
  virtual const std::string User() const = 0;

  /**
   * @brief Gets the domain associated with the user from whom consent is requested
   * 
   * @return Domain associated with the user from whom consent is requested
   */
  virtual const std::string Domain() const = 0;
};
} // namespace mip

#endif // API_MIP_RMS_CONSENT_H_
