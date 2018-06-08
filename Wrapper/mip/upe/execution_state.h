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
 * @brief This file contains the ExecutionState class.
 *
 * @file execution_state.h
 */
#ifndef API_MIP_UPE_EXECUTION_STATE_H_
#define API_MIP_UPE_EXECUTION_STATE_H_

#include <string>
#include <utility>
#include <vector>

#include "mip/common_types.h"
#include "mip/upe/action.h"
namespace mip {

/**
 * @brief Interface for all the state needed to execute the engine.
 *
 * @note Clients should only call the methods to obtain the state that is needed.
 * Hence, for efficiency, clients may want to implement this interface such that
 * the corresponding state is computed dynamically instead of computing in advance.
 */
class ExecutionState {
public:
  /**
   * @brief Gets the sensitivity label id that should be applied on the document.
   *
   * @return sensitivity label id to be applied to the content if exists else empty to remove label.
   */
  virtual std::string GetNewLabelId() const = 0;

  /**
   * @brief Implementation should pass whether or not justification to downgrade an existing label was given.
   *
   * @return true if downgrade is already justified, false if it hasn't yet been justified.
   * @see mip::JustifyAction
   */
  virtual bool IsDowngradeJustified() const = 0;

  /**
   * @brief Get the new label's assignment method.
   * 
   * @return the assignment method STANDARD, PRIVILEGED, AUTO.
   * @see mip::AssignmentMethod
   */
  virtual AssignmentMethod GetNewLabelAssignmentMethod() const = 0;

  /**
   * @brief Get the meta-data items from the content.
   * 
   * @return a vector of key value pairs representing the meta data applied to the content.
   * @note Each meta-data item is a pair of name and value.
   */
  virtual std::vector<std::pair<std::string, std::string>> GetContentMetadata(
      const std::vector<std::string>& names,
      const std::vector<std::string>& namePrefixes) const = 0;

  /**
   * @brief Gets the rights managment service protection template id.
   * 
   * @return the rights managment service protection template id if exists else in a guid format without braces, return an empty string.
   */
  virtual std::string GetTemplateId() const = 0;

  /**
   * @brief Gets the content format.
   * 
   * @return DEFAULT, EMAIL
   * @see mip::ContentFormat
   */
  virtual ContentFormat GetContentFormat() const = 0;
  /**
  * @brief Return a list of actions that the application supports. All actions types are listed in mip/upe/action.h
  */
  virtual const ActionType GetSupportedActions() const = 0;

  /** @cond DOXYGEN_HIDE */  
  virtual ~ExecutionState() { }

protected:
  ExecutionState() { }
  /** @endcond */
};

}  // namespace mip

#endif  // API_MIP_UPE_EXECUTION_STATE_H_
