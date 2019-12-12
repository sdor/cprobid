import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { MsmsExperimentsComponent } from './msms-experiments.component';

describe('MsmsExperimentsComponent', () => {
  let component: MsmsExperimentsComponent;
  let fixture: ComponentFixture<MsmsExperimentsComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ MsmsExperimentsComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(MsmsExperimentsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
