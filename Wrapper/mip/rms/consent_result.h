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
 * @brief Defines ConsentResult class
 * 
 * @file consent_result.h
 */

#ifndef API_MIP_RMS_CONSENT_RESULT_H_
#define API_MIP_RMS_CONSENT_RESULT_H_

#include <string>

namespace mip {
/**
 * @brief Describes result of consent request after user interaction
 */
class ConsentResult {
public:
  /**
   * @brief ConsentResult constructor
   * 
   * @param accepted Whether or not user consented to action
   * @param showAgain Whether or not explicit consent is required for future action requests
   * @param userId User (email address) from whom consent was requested
   */
  ConsentResult(bool accepted = false, bool showAgain = true, const std::string& userId = "undef")
      : mAccepted(accepted),
        mShowAgain(showAgain),
        mUserId(userId) {}

  /**
   * @brief Gets whether or not user consented to action
   * 
   * @return Whether or not user contented to action
   */
  bool Accepted() const { return mAccepted; }

  /**
   * @brief Gets whether or not explicit consent is required for future requests
   * 
   * @return Whether or not explicit consent is required for future requests
   * 
   * @note If this is true, the SDK will remember the result of this consent and not prompt the client application for
   * consent in the future.
   */
  bool ShowAgain() const { return mShowAgain; }

  /**
   * @brief Gets user (email address) from whom consent was requested
   * 
   * @return User from whom consent was requested
   */
  const std::string& UserId() const { return mUserId; }

private:
  bool mAccepted;
  bool mShowAgain;
  std::string mUserId;
};
} // namespace mip

#endif // API_MIP_RMS_CONSENT_RESULT_H_
