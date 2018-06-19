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
 * @brief Defines TemplateDescriptor interface
 * 
 * @file template_descriptor.h
 */

#ifndef API_MIP_RMS_TEMPLATE_DESCRIPTOR_H_
#define API_MIP_RMS_TEMPLATE_DESCRIPTOR_H_

//#include <future>
#include <vector>

#include "mip/common_types.h"
#include "mip/mip_export.h"

namespace mip {
/**
 * @brief Describes an RMS template
 */
class TemplateDescriptor {
public:

// TODO: This code depends on the "#include <future>" part of the STL library, which is unsupported in C++/CLI.

  ///**
  // * @brief Get collection of templates available to a user
  // *
  // * @param userId The email address of the user for whom the templates
  // *  are being retrieved. This email address will be used to discover the RMS
  // *  service instance (either ADRMS server or Azure RMS) that the user's
  // *  organization is using. This parameter is also used as a hint for userId
  // *  for user authentication, i.e., it will be passed to
  // *  AuthDelegate.AcquireOAuth2Token() in the AuthenticationParameters
  // *  structure.
  // * @param authenticationCallback Callback to utilize for auth
  // * @param launchType Async launch type
  // * @param cancelState Cancellation token to allow application to cancel this operation at any time
  // *
  // * @return Collection of templates available to a user
  // */
  //MIP_EXPORT static std::shared_future<std::vector<std::shared_ptr<TemplateDescriptor>>> GetTemplateListAsync(
  //  const std::string& userId,
  //  mip::AuthDelegate& authenticationCallback,
  //  std::launch launchType,
  //  std::shared_ptr<std::atomic<bool>> cancelState = nullptr);

  /**
   * @brief Gets template id
   * 
   * @return Template id
   */
  virtual std::string TemplateId() const = 0;

  /**
   * @brief Gets template name
   * 
   * @return Template name
   */
  virtual std::string Name() const = 0;

  /**
   * @brief Gets template description
   * 
   * @return Template description
   */
  virtual std::string Description() const = 0;

  /** @cond DOXYGEN_HIDE */
  virtual ~TemplateDescriptor() {}

protected:
  TemplateDescriptor() {}
  /** @endcond */
};
  
} // namespace mip

#endif // API_MIP_RMS_TEMPLATE_DESCRIPTOR_H_
