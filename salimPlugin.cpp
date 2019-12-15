#include <orthanc/OrthancCPlugin.h>

#include <string.h>
#include <stdio.h>

static OrthancPluginContext* context = NULL;

extern "C"
{

ORTHANC_PLUGINS_API OrthancPluginErrorCode OnStoredCallback(OrthancPluginDicomInstance* instance,
                                                          const char* instanceId)
{

  char buffer[256];
  
  
}


ORTHANC_PLUGINS_API int32_t OrthancPluginInitialize(OrthancPluginContext* c)
{
  char info[1024], *s;

  context = c;
  OrthancPluginLogWarning(context, "Sample plugin is initializing");

  /* Check the version of the Orthanc core */
  if (OrthancPluginCheckVersion(c) == 0)
  {
    sprintf(info, "Your version of Orthanc (%s) must be above %d.%d.%d to run this plugin",
            c->orthancVersion,
            ORTHANC_PLUGINS_MINIMAL_MAJOR_NUMBER,
            ORTHANC_PLUGINS_MINIMAL_MINOR_NUMBER,
            ORTHANC_PLUGINS_MINIMAL_REVISION_NUMBER);
    OrthancPluginLogError(context, info);
    return OrthancPluginErrorCode_InternalError;
  }

  /* Print some information about Orthanc */
  sprintf(info, "The version of Orthanc is '%s'", context->orthancVersion);
 

  return OrthancPluginErrorCode_Success;
}


ORTHANC_PLUGINS_API void OrthancPluginFinalize()
{
  OrthancPluginLogWarning(context, "salim Plugin is finalizing");
}


ORTHANC_PLUGINS_API const char* OrthancPluginGetName()
{
  return "salimPlugin";
}


ORTHANC_PLUGINS_API const char* OrthancPluginGetVersion()
{
  return "1.0";
}

}