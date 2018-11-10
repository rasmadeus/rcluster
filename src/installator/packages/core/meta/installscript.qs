function Component()
{
}

Component.prototype.createOperations = function()
{
    try
    {
        component.createOperations();
        if (installer.value("os") === "win")
        {
            component.addElevatedOperation("Execute", "{0,3010}", "@TargetDir@/vc_redist.x86.exe", "/norestart", "/q");
            component.addOperation("CreateShortcut", "@TargetDir@/core_controller.exe", "@StartMenuDir@/RBarCoreController.lnk");
            component.addOperation("CreateShortcut", "@TargetDir@/core_controller.exe", "@DesktopDir@/RBarCoreController.lnk");
            component.addOperation("CreateShortcut", "@TargetDir@/core_server.exe", "@StartMenuDir@/RBarCoreServer.lnk");
            component.addOperation("CreateShortcut", "@TargetDir@/core_server.exe", "@DesktopDir@/RBarCoreServer.lnk");
            component.addOperation("CreateShortcut", "@TargetDir@/supervisor.exe", "@StartMenuDir@/RBarSupervisor.lnk");
            component.addOperation("CreateShortcut", "@TargetDir@/supervisor.exe", "@DesktopDir@/RBarSupervisor.lnk");
            component.addOperation("CreateShortcut", "@TargetDir@/maintenancetool.exe", "@StartMenuDir@/RBarUninstall.lnk");
        }
    }
    catch(ex)
    {
        print(e);
    }
}
