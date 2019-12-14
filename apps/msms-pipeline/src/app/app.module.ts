import { AuthGuardGuard } from './auth-guard.guard';

import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { AppComponent } from './app.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
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
import { JwtModule } from "@auth0/angular-jwt";
import { HTTP_INTERCEPTORS } from '@angular/common/http';
import { JwtTokenInterceptor } from './jwt-token.interceptor';

const routes: Routes = [
  {path: '', redirectTo: '/msms-experiments', pathMatch: 'full'},
  {path: 'msms-experiments', component: MsmsExperimentsComponent , canActivate: [AuthGuardGuard]},
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
    HttpClientModule,
    JwtModule.forRoot({
      config: {
        tokenGetter:() => {
          return localStorage.getItem("auth_token");
        },
        whitelistedDomains: ["localhost","localhost:4200"],
        blacklistedRoutes: ["/api/users","/api/users/sign_in"]
      }
    }),
    ReactiveFormsModule,
    MatPaginatorModule,
    MatToolbarModule,
    MatInputModule,
    MatProgressSpinnerModule,
    MatIconModule,
    MatTooltipModule,
    MatButtonModule,

  ],
  providers: [
    { provide: HTTP_INTERCEPTORS, useClass: JwtTokenInterceptor, multi: true },
  ],
  bootstrap: [AppComponent]
})
export class AppModule {}
