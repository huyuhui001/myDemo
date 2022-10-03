sap.ui.define(
    [
      "sap/ui/core/mvc/Controller",
      "sap/base/Log"
    ],
    /**
     * @param {typeof sap.ui.core.mvc.Controller} BaseController
     */
    function (BaseController, Log) {
        "use strict";

        return BaseController.extend("tutorial.me.myappui5.controller.SplitApp", {
            onInit() {},

            onListItemSelect: function (oEvent) {
              const sToPageId = oEvent.getParameter("item").getCustomData()[0].getValue();

              // @ts-ignore
              this.getSplitAppObj().toDetail(this.createId(sToPageId));
            },

            getSplitAppObj: function () {
              const result = this.byId("splitApp");
              if (!result) {
                Log.info("SplitApp object can't be found");
              }
              return result;
            }
        });
    }
);
