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

#ifndef API_MIP_FILE_FILE_HANDLER_H_
#define API_MIP_FILE_FILE_HANDLER_H_

#include <memory>

#include "mip/stream.h"
#include "mip/file/labeling_options.h"
#include "mip/rms/user_policy.h"
#include "mip/upe/content_label.h"

namespace mip {

/**
 * @brief Interface for all file handling functions.
 */
class FileHandler {
public:

  /**
   * @brief Observer interface for clients to get notifications for file handler related events.
   * 
   * @note If an *Error event occurs, error object holds inside mip::Error class.
   * @note Client should not call the engine back on the thread that calls the observer.
   */
  class Observer {
  public:
    virtual ~Observer() {}

    /**
     * @brief Called when the label is retrieved (from the file) successfully.
     */
    virtual void OnGetLabelSuccess(const std::shared_ptr<ContentLabel>& label, const std::shared_ptr<void>& context) = 0;

    /**
     * @brief Called when retrieving the label (from the file) failed due to an error.
     */
    virtual void OnGetLabelFailure(const std::exception_ptr& error, const std::shared_ptr<void>& context) = 0;

    /**
     * @brief Called when the protection policy is retrieved (from the file) successfully.
     */
    virtual void OnGetProtectionSuccess(const std::shared_ptr<UserPolicy>& userPolicy, const std::shared_ptr<void>& context) = 0;

    /**
     * @brief Called when retrieving the protection policy (from the file) failed due to an error.
     */
    virtual void OnGetProtectionFailure(const std::exception_ptr& error, const std::shared_ptr<void>& context) = 0;

    /**
     * @brief Called when committing the changes to the file were successful.
     */
    virtual void OnCommitSuccess(bool commited, const std::shared_ptr<void>& context) = 0;

    /**
     * @brief Called when committing the changes to the file failed due to an error.
     */
    virtual void OnCommitFailure(const std::exception_ptr& error, const std::shared_ptr<void>& context) = 0;

  protected:
    Observer() {}
  };

  /**
   * @brief Starts retrieving the sensitivity label from the file.
   * 
   * @note FileHandler::Observer will be called upon success or failure.
   * 
   * @param context Client context that will be opaquely passed back to the observer.
   */
  virtual void GetLabelAsync(const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Starts retrieving the protection policy from the file.
   * 
   * @note FileHandler::Observer will be called upon success or failure.
   * 
   * @param context Client context that will be opaquely passed back to the observer.
   */
  virtual void GetProtectionAsync(const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Sets the sensitivity label to the file.
   * 
   * @note Changes will not be written to the file until CommitAsync will be called.
   * 
   * @warning Throws JustificationRequiredError when setting the label requires a justification and no justification message was provided via the labelingOptions parameter.
   */
  virtual void SetLabel(const std::string& labelId, const LabelingOptions& labelingOptions) = 0;

  /**
  * @brief Deletes the sensitivity label from the file.
  * 
  * @note Changes will not be written to the file until CommitAsync will be called.
  *       Privilegd and Auto method allows the API to override any existing label
  * @warning Throws JustificationRequiredError when setting the label requires a justification and no justification message was provided via the justificationMessage parameter.
  */
  virtual void DeleteLabel(AssignmentMethod method, const std::string& justificationMessage) = 0;

  /**
   * @brief Sets custom permissions to the file.
   * 
   * @note Changes will not be written to the file until CommitAsync will be called.
   */
  virtual void SetCustomPermissions(const std::shared_ptr<PolicyDescriptor>& policyDescriptor) = 0;

  /**
   * @brief Removes protection from the file. If the file is labeled, the label will be lost.
   * 
   * @note Changes will not be written to the file until CommitAsync will be called.
   */
  virtual void RemoveProtection() = 0;

  /**
   * @brief Writes the changes to the file specified by the |outputFilePath| parameter.
   * 
   * @note FileHandler::Observer will be called upon success or failure.
   */
  virtual void CommitAsync(const std::string& outputFilePath, const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Writes the changes to the stream specified by the |outputStream| parameter.
   * 
   * @note FileHandler::Observer will be called upon success or failure.
   */
  virtual void CommitAsync(const std::shared_ptr<Stream>& outputStream, const std::shared_ptr<void>& context) = 0;

  /**
   * @brief Calculates the output file name and extension based on the original file name and the accumulated changes.
   */
  virtual std::string GetOutputFileName() = 0;

  virtual ~FileHandler() {}

protected:
  FileHandler() {}
};

} //namespace mip

#endif // API_MIP_FILE_FILE_HANDLER_H_
