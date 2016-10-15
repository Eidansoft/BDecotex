class ControllerFamily
{
    static dependencies = [ControllerFamily];
    
    constructor()
    {
        
    }

}

// Register the controller with Angular
bdecotexApp.controller(
	'ControllerFamily', ControllerFamily.dependencies);
