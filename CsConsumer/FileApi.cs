using NetMip;
using System;
using System.Collections.Generic;
using System.IO;

namespace CsConsumer
{
    public sealed class FileApi
    {
        AuthDelegate authDelegate;
        FileProfile profile;
        FileEngine engine;

        public FileApi(
            ITokenProvider tokenProvider,
            string applicationId,
            string applicationName,
            string storagePath)
        {
            this.authDelegate = new AuthDelegateImpl(tokenProvider);

            var applicationInfo = new ApplicationInfo(
                applicationId,
                applicationName);

            var settings = new FileProfile.Settings(storagePath, false, authDelegate, applicationInfo);

            var lateFileProfile = new LateValue<FileProfile>();

            FileProfile.LoadAsync(settings, lateFileProfile);
            this.profile = lateFileProfile.AwaitValue();


            FileEngine.Settings engineSettings = new FileEngine.Settings("1234", "");

            var lateFileEngine = new LateValue<FileEngine>();

            this.profile.AddEngineAsync(engineSettings, lateFileEngine);
            this.engine = lateFileEngine.AwaitValue();
        }

        public string GetSdkVersion()
        {
            return FileProfile.GetSdkVersion();
        }

        public string GetEngineId()
        {
            return engine.GetSettings().Id;
        }

        public ICollection<Label> ListLabels()
        {
            return engine.ListSensitivityLabels();
        }

        public string GetFileLabel(string filePath)
        {
            if (this.engine == null)
                return null;

            try
            {
                var handler = this.engine.CreateFileHandler(filePath);

                LateValue<ContentLabel> lateContentLabel = new LateValue<ContentLabel>();
                handler.GetLabelAsync(lateContentLabel);
                ContentLabel contentLabel = lateContentLabel.AwaitValue();

                if (contentLabel != null)
                    return contentLabel.Label.Name;

                return null;
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        public string GetFileLabel(Stream stream, string inputFileName)
        {
            if (this.engine == null)
                return null;

            try
            {
                var handler = this.engine.CreateFileHandler(stream, inputFileName);

                LateValue<ContentLabel> lateContentLabel = new LateValue<ContentLabel>();
                handler.GetLabelAsync(lateContentLabel);
                ContentLabel contentLabel = lateContentLabel.AwaitValue();

                if (contentLabel != null)
                    return contentLabel.Label.Name;

                return null;
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        public bool SetFileLabel(string filePath, string outputFile, string labelId)
        {
            if (engine == null)
                return false;

            try
            {
                FileHandler handler = engine.CreateFileHandler(filePath);
                handler.SetLabel(labelId, new LabelingOptions(AssignmentMethod.Privileged, string.Empty));

                LateValue<bool> lateResult = new LateValue<bool>();
                handler.CommitAsync(outputFile, lateResult);

                bool wasCommitted = lateResult.AwaitValue();
                return wasCommitted;
            }
            catch (Exception ex)
            {
                return false;
                //throw;
            }
        }
    }
}
