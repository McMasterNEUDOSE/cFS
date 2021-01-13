pipeline {
    agent any
    
    stages {
        stage('Build') {
            steps {
                cmakeBuild
                    buildDir : 'build',
                    sourceDir : '/var/lib/jenkins/workspace/cFS/cfe',
                    installation : 'InSearchPath',
                    steps : [
                        [envVars: DCMAKE_INSTALL_PREFIX=/exe , DCMAKE_BUILD_TYPE=debug ]     
                    ]
            }
        }
    }
}
