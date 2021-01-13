pipeline {
    agent any
    
    stages {
        stage('Build') {
            steps {
                cmakeBuild
                    installation: 'InSearchPath',
            }
        }
    }
}
