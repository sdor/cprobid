import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { AppComponent } from './app.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { AngularTokenModule } from 'angular-token';
import { AngularTokenService } from 'angular-token';
import { SigninComponent } from './signin/signin.component';
import { SignupComponent } from './signup/signup.component';
import { MsmsExperimentsComponent } from './msms-experiments/msms-experiments.component';
import { PageNotFoundComponentComponent } from './page-not-found-component/page-not-found-component.component';
import { NavBarComponent } from './nav-bar/nav-bar.component';
import {MatToolbarModule} from '@angular/material/toolbar';
import {MatPaginatorModule} from '@angular/material/paginator';
import {MatInputModule} from '@angular/material/input';
import {MatProgressSpinnerModule} from '@angular/material/progress-spinner';
import {MatIconModule} from '@angular/material/icon';
import {MatTooltipModule} from '@angular/material/tooltip';
import {MatButtonModule} from '@angular/material/button';
import { HttpClientModule } from '@angular/common/http';
import { ReactiveFormsModule } from '@angular/forms';

const routes: Routes = [
  {path: '', redirectTo: '/msms-experiments', pathMatch: 'full'},
  {path: 'msms-experiments', component: MsmsExperimentsComponent, canActivate: [AngularTokenService]},
  {path: 'signin', component: SigninComponent},
  {path: 'signup', component: SignupComponent},
  {path: '**', component: PageNotFoundComponentComponent }
]
@NgModule({
  declarations: [
    AppComponent,
    SigninComponent,
    SignupComponent,
    MsmsExperimentsComponent,
    PageNotFoundComponentComponent,
    NavBarComponent
  ],
  imports: [
    BrowserModule,
    BrowserAnimationsModule,
    RouterModule.forRoot(
      routes,
      { enableTracing: true } // <-- debugging purposes only
    ),
    AngularTokenModule.forRoot({
      apiBase: 'api',
      signInRedirect: 'signin'
    }),
    HttpClientModule,
    ReactiveFormsModule,
    MatPaginatorModule,
    MatToolbarModule,
    MatInputModule,
    MatProgressSpinnerModule,
    MatIconModule,
    MatTooltipModule,
    MatButtonModule,

  ],
  providers: [AngularTokenModule],
  bootstrap: [AppComponent]
})
export class AppModule {}
