module.exports = {
  name: 'msms-pipeline',
  preset: '../../jest.config.js',
  coverageDirectory: '../../coverage/apps/msms-pipeline',
  snapshotSerializers: [
    'jest-preset-angular/AngularSnapshotSerializer.js',
    'jest-preset-angular/HTMLCommentSerializer.js'
  ]
};
