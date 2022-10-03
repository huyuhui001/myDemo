# Reference of learning materials

[Develop Your First SAPUI5 Web App on Cloud Foundry](https://developers.sap.com/mission.sapui5-cf-first.html)	
[Deliver Your First SAP Fiori Launchpad Site](https://developers.sap.com/mission.cp-starter-digitalexp-portal.html)	
[Introducing the easy-ui5 generator](https://blogs.sap.com/2019/02/05/introducing-the-easy-ui5-generator/)
[Easy-UI5 3.0 – From Community Contributions to Community Plugins](https://blogs.sap.com/2021/04/09/easy-ui5-3.0-from-community-contributions-to-community-plugins/)
[Build an Application End-to-End Using CAP, Node.js and VS Code](https://developers.sap.com/mission.btp-application-cap-e2e.html)

# Install CF CLI

[Installation guide](https://docs.cloudfoundry.org/cf-cli/install-go-cli.html)

Ubuntu based installation.
```
wget -q -O - https://packages.cloudfoundry.org/debian/cli.cloudfoundry.org.key | sudo apt-key add -
echo "deb https://packages.cloudfoundry.org/debian stable main" | sudo tee /etc/apt/sources.list.d/cloudfoundry-cli.list
sudo apt-get update
sudo apt-get install cf8-cli
```
MacOS based:
```
brew install cloudfoundry/tap/cf-cli@8
```



# Install CF mta plugin

[Installation guide](https://developers.sap.com/tutorials/cp-cf-install-cliplugin-mta.html).

Linux, MacOS and Windows based installation.
```
cf install-plugin -f https://github.com/cloudfoundry-incubator/multiapps-cli-plugin/releases/latest/download/multiapps-plugin.linux64
cf install-plugin -f https://github.com/cloudfoundry-incubator/multiapps-cli-plugin/releases/latest/download/multiapps-plugin.osx
cf install-plugin -f https://github.com/cloudfoundry-incubator/multiapps-cli-plugin/releases/latest/download/multiapps-plugin.win64.exe
```
Verify:
```
cf deploy --help
```

# Install VSCode extensions

Two VSCode extensions are needed:

1. sap cds language support
2. SAP Fiori Tools - Extension Pack


# Install node packages

Install required Nodejs packages.
```
npm install --global @sap/cds-dk
npm install --global @sap/cds-compiler
npm install --global @sap/cds-foss
npm install --global @sap/eslint-plugin-cds
npm install --global @sap/cds-mtx

npm install --global @ui5/cli
npm install --global yo
npm install --global generator-easy-ui5
npm install --global mbt

npm install --global node-run-cmd
```


# CF enviornment

Get below key information from BTP trial account:

* Subaccount Name
* CF AIP endpoint
* CF Spaces

Log on to CF API endpoint
```
cf login -a <your_cf_api_endpoint>
```

Get key info via cf commandline.
```
cf orgs
cf spaces
cf apps
```

Enable space ssh acccess.
```
cf space 
cf space <your_cf_space_name>
cf allow-space-ssh <your_cf_space_name>
cf space-ssh-allowed <your_cf_space_name>
```

Enable app ssh access.
```
cf enable-ssh <your_cf_app_name>
cf ssh-enabled <your_cf_app_name>
cf <your_cf_app_name>
```



# Initialize UI5 Project

Command:
```
yo easy-ui5 project
```
Questions and Answers:

* What do you want to do? `Create a new OpenUI5/SAPUI5 project [app]`
* How do you want to name this project? `myappui5`
* Which namespace do you want to use? `tutorial.me`
* Do you want to enable the SAP Fiori elements flexible programming model? `No`
* On which platform would you like to host the application? `Application Router @ Cloud Foundry`
* Which view type do you want to use? `XML`
* Where should your UI5 libs be served from? `Content delivery network (SAPUI5)`
* Would you like to create a new directory for the project? `Yes`
* Would you like to add JavaScript code assist libraries to the project? `Yes`
* Would you like to initialize a local git repository for the project? `Yes`

Add CDS features.
```
cd tutorial.me.myappui5
cds add xsuaa --for production
cds add hana --for production
```

Add below new lines to in files `/package.json` and `/approuter/package.json` specify engine version. It's [known issiue](https://github.com/SAP-samples/cloud-sample-node-chat/issues/3).
```
  "engines": {
    "node": "16.X"
  },
```

Create file `SplitApp.controller.js` with statement `return BaseController.extend("tutorial.me.myappui5.controller.SplitApp"` to define to init page and corresponding actions.

Create file `SplitApp.view.xml` to add page content with SplitApp layout view. 

Edit file `manifest.json`.
```
{
  ...
  "sap.ui5": {
    ...
    "routing": {
      ...
      "targets": {
        "TargetMainView": {
          "viewType": "XML",
          "transition": "slide",
          "clearControlAggregation": false,
          "viewId": "SplitApp",
          "viewName": "SplitApp"
        }
      }
    },
    "rootView": {
      "viewName": "tutorial.me.myappui5.view.SplitApp",
      "type": "XML",
      "async": true,
      "id": "SplitApp"
    }
  }
}
```

Update `mta.yaml` file with minimal setting for pure UI5 features.
```
ID: myappui5
_schema-version: 3.2.0
version: 0.0.1
parameters:
  enable-parallel-deployments: true
modules:
  - name: myappui5
    type: nodejs
    path: approuter
    parameters:
      disk-quota: 512M
      memory: 512M
    requires:
      - name: myappui5_destination
    build-parameters:
      builder: custom
      commands:
        - npm install
        - npm run build:ui --prefix ..
resources:
  - name: myappui5_destination
    type: org.cloudfoundry.managed-service
    parameters:
      service-plan: lite
      service: destination
      config:
        HTML5Runtime_enabled: true
        version: 1.0.0
```

Build and deploy the application.
```
mbt build
npm run deploy
```

Access the web link to verify the result.
```
https://<your_org_name>-<your_cf_space_name>-<your_project_name>.cfapps.<your_domain_name_of_cf_endpoint>/uimodule/index.html
```















