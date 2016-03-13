<?php
require_once (dirname(__FILE__).'/BDecotexView.php');
require_once "./FamilyView.php.inc";
require_once "../libs/fastRoute/bootstrap.php";

/**
 * Description of FamilyView
 *
 * @author alex
 */
class MainView extends BDecotexView{
    const FAMILY_VIEW = 0;
    
    protected $httpMethod;
    protected $uri;

    public function __construct() {
        $dispatcher = FastRoute\simpleDispatcher(function(FastRoute\RouteCollector $r) {
            $r->addRoute(['GET', 'POST', 'DELETE', 'PUT'], '/bdecotex/family[/{params:.+}]', MainView::FAMILY_VIEW);
        });
        parent::__construct($dispatcher);
    }
    
    public function processUri($httpMethod, $uri) {
        $this->httpMethod = $httpMethod;
        $this->uri = $uri;
        parent::processUri($httpMethod, $uri);
    }

    protected function processHandler($handler, $vars) {
        switch ($handler) {
            case MainView::FAMILY_VIEW:
                $view = new FamilyView();
                $view->processUri($this->httpMethod, $this->uri);
                break;
        }
    }
}
